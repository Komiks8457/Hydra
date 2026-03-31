#include "GlobalManager.h"
#include "BSLib/AppLogger.h"
#include "HydraFramework.h"
#include "utils/MemoryUtility.h"
#include "Classes/GlobalMainProcess.h"
#include "BSLib/Database/DbManager.h"

CGlobalManager* g_pGlobalManager = NULL;

class MsgValidator {
public:
    int __thiscall ValidateMsg(void* pSession, int opcode, int a4)
    {
        if (opcode == 0x623D) {
            return 0;
        }
        return reinterpret_thiscall(0x0175CBF0, int, this, pSession, opcode, a4);
    }
};

int GlobalManager_WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    //dword_1868950 = (int)&dword_1856948;
    MEMUTIL_WRITE_VALUE(uintptr_t, 0x01868950, 0x01856948);

    //assign our g_pGlobalManager global pointer
    g_pGlobalManager = *(CGlobalManager**)0x01868950; // or (CGlobalManager*)0x01856948;

    //Logger::warn2("g_pGlobalManager = CGlobalManager Instance (0x%p)", g_pGlobalManager);

    //return sub_170C6F0(0, "GlobalManager", hInstance, (int)lpCmdLine, 1, 0);
    return reinterpret_cdecl(0x0170C6F0, int, 0, "GlobalManager", hInstance, lpCmdLine, 1, 0);
}

void CGlobalManager::Initialize()
{
    // Hook LogWriter first
    CAppLogger::SetupHook(0x0170B690);

    // Other hooks
    CGlobalMainProcess::SetupHook();

    // CGlobalManager vftable hooks
    MEMUTIL_VFTABLE_HOOK(0x01802BAC,  1, &CGlobalManager::init_module);
    MEMUTIL_VFTABLE_HOOK(0x01802BAC, 11, &CGlobalManager::init_localdata);

    // WinMain hook
    MEMUTIL_REPLACE_OFFSET(0x017B274D, &GlobalManager_WinMain);

    // MsgValidation hook
    //MEMUTIL_REPLACE_OFFSET(0x0172C017, &MsgValidator::ValidateMsg);
}

BOOL CGlobalManager::init_module()
{
    HydraFramework::CMainProcess::CreateInstance(this, "GlobalManager");

    if (!g_pHydraMainProcess) {
        PutLog(FATAL, "Failed to initialize HydraFramework::CMainProcess.");
        return FALSE;
    }

    HydraFramework::CRefDataManager::CreateInstance();

    if (!g_pRDM) {
        PutLog(FATAL, "Failed to initialize HydraFramework::CRefDataManager.");
        return FALSE;
    }

    CDbManager::CreateInstance(10, 20);

    if (!g_pDbMgr) {
        PutLog(FATAL, "Failed to initialize CDbManager.");
        return FALSE;
    }

    MEMUTIL_WRITE_POINTER(0x018056D0, GlobalData::SecretKey, sizeof(GlobalData::SecretKey));
    Logger::info2("New secret key applied: \"%s\"", (const char*)0x018056D0);

    return reinterpret_thiscall(0x0172A540, BOOL, this);
}

BOOL CGlobalManager::init_localdata()
{
    const std::string &database = g_pHydraMainProcess->GetSettingFile();
    const std::string &version  = g_pHydraMainProcess->GetVersion();

    PutLog(FATAL, "*******************************************************************");
    PutLog(FATAL, "[SROR] HydraFramework was initialized successfully");
    PutLog(FATAL, "%s %s Compiled (%s)", __DATE__, __TIME__, version.c_str());
    PutLog(FATAL, "*******************************************************************");

    switch (g_pDbMgr->InitDB(database))
    {
        case -999:
            PutLog(FATAL, "Failed to read %s", database.c_str());
            return FALSE;
        case -1:
            PutLog(FATAL, "Cannot find AccountDB entry in %s", database.c_str());
            return FALSE;
        case -2:
            PutLog(FATAL, "Cannot connect to AccountDB, please check %s", database.c_str());
            return FALSE;
        case -3:
            PutLog(FATAL, "Cannot find ShardDB entry in %s", database.c_str());
            return FALSE;
        case -4:
            PutLog(FATAL, "Cannot connect to ShardDB, please check %s", database.c_str());
            return FALSE;
        case -5:
            PutLog(FATAL, "Cannot find LogDB entry in %s", database.c_str());
            return FALSE;
        case -6:
            PutLog(FATAL, "Cannot connect to LogDB, please check %s", database.c_str());
            return FALSE;
    }

    switch (g_pRDM->InitializeData())
    {
        case -65535:
            PutLog(FATAL, "g_pDbMgr is NULL.");
            return FALSE;
        case -65534:
            PutLog(FATAL, "Failed loading RefObjItem.");
            return FALSE;
        case -65533:
            PutLog(FATAL, "Failed loading RefObjChar.");
            return FALSE;
        case -65532:
            PutLog(FATAL, "Failed loading RefSkill.");
            return FALSE;
    }

    //HWND phWnd = g_pGlobalManager->GetWinHandle();
    //ShowWindow(phWnd, SW_HIDE);

    return reinterpret_thiscall(0x01674DF0, BOOL, this);
}

HWND CGlobalManager::GetWinHandle()
{
    DWORD dwSvrFrameWin = (*(DWORD*)0x0186981C); //ServerFramework::CServerFrameWindow
    return (dwSvrFrameWin ? *(HWND*)MEMUTIL_ADD_PTR(dwSvrFrameWin, 0x14) : NULL);
}

uint8_t CGlobalManager::GetServerBodyID(const char* moduleName)
{
    int pModule = reinterpret_cdecl(0x01722030, int, moduleName);
    if (!pModule) return NULL;
    return *(unsigned char*)pModule;
}
