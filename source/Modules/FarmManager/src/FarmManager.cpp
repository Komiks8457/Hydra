#include "FarmManager.h"
#include "BSLib/AppLogger.h"
#include "HydraFramework.h"
#include "BSLib/NetEngine/NetEngine.h"
#include "utils/MemoryUtility.h"
#include "Classes/FarmMainProcess.h"

CFarmManager* g_pFarmManager = NULL;

class CMsgValidator {
public:
    int __thiscall ValidateMsg(void* pSession, int opcode, int a4)
    {
        if (opcode == 0x623D) {
            return 0;
        }

        return reinterpret_thiscall(0x014930D0, int, this, pSession, opcode, a4);
    }
};

int FarmManager_WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    //dword_156FF40 = (int)&dword_154EE60;
    MEMUTIL_WRITE_VALUE(uintptr_t, 0x0156FF40, 0x0154EE60);

    //assign our g_pFarmManager global pointer
    g_pFarmManager = *(CFarmManager**)0x0156FF40; // or (CFarmManager*)0x0154EE60;

    Logger::warn2("g_pFarmManager = CFarmManager Instance (0x%p)", g_pFarmManager);

    //return sub_1459A50(0, "FarmManager", (int)hInstance, (int)lpCmdLine, 1, 0);
    return reinterpret_cdecl(0x01459A50, int, 0, "FarmManager", hInstance, (int)lpCmdLine, 1, 0);
}

void CFarmManager::Initialize()
{
    // 1. Hook LogWriter first
    CAppLogger::SetupHook(0x01457B70);

    // Other hooks
    CFarmManagerMainProcess::SetupHook();

    // CFarmManager vftable hooks
    MEMUTIL_VFTABLE_HOOK(0x01529BE4,  1, &CFarmManager::init_module);
    MEMUTIL_VFTABLE_HOOK(0x01529BE4, 11, &CFarmManager::init_localdata);

    // WinMain hook
    MEMUTIL_REPLACE_OFFSET(0x014F153D, &FarmManager_WinMain);

    // MsgValidation hook
    MEMUTIL_REPLACE_OFFSET(0x01455CF7, &CMsgValidator::ValidateMsg);
}

BOOL CFarmManager::init_module()
{
    HydraFramework::CMainProcess::CreateInstance(this, "FarmManager");

    if (!g_pHydraMainProcess) {
        PutLog(FATAL, "Failed to initialize Hydra");
        return FALSE;
    }

    return reinterpret_thiscall(0x014540E0, BOOL, this);
}

BOOL CFarmManager::init_localdata()
{
    if (!g_pHydraMainProcess) {
        PutLog(FATAL, "Failed to initialize Hydra");
        return FALSE;
    }

    CMsg *ddd = NEWMSG(0x623D, FALSE);

    if (ddd)
    {
        const std::string& moduleName = g_pHydraMainProcess->GetModuleName(this);
        uint8_t serverBody = GetServerBodyID(moduleName.c_str());

        HydraFramework::SessionInfo test;
        test.wServerBodyID = serverBody;
        test.szName = moduleName.c_str();

        ddd->WriteUInt8(1);
        //ddd->Write<HydraFramework::SessionInfo>(test);

        //ddd->PrintDumpData(__FUNCTION__);
        SENDMSG(1, ddd);
        DELMSG(ddd);
    }

    return reinterpret_thiscall(0x01441250, BOOL, this);
}

uint8_t CFarmManager::GetServerBodyID(const char* moduleName)
{
    int pModule = reinterpret_cdecl(0x01472D20, int, moduleName);
    if (!pModule) return NULL;
    return *(unsigned char*)pModule;
}
