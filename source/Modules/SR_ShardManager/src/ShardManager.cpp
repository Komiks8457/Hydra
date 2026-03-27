#include "ShardManager.h"
#include "BSLib/AppLogger.h"
#include "HydraFramework.h"
#include "utils/MemoryUtility.h"
#include "Classes/ShardMainProcess.h"
#include "BSLib/Database/DbManager.h"

CShardManager *g_pShardManager = NULL;

int ShardManager_WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    //dword_D19008 = (int)&dword_CDE830;
    MEMUTIL_WRITE_VALUE(uintptr_t, 0x00D19008, 0x00CDE830);

    //assign our g_pGlobalManager global pointer
    g_pShardManager = *(CShardManager**)0x00D19008; // or (CShardManager*)0x00CDE830;

    Logger::warn2("g_pShardManager = CShardManager (0x%p)", g_pShardManager);

    //return sub_9D8E90(0, (CHAR *)"SR_ShardManager", hInstance, (int)lpCmdLine, 1, 0);
    return reinterpret_cdecl(0x009D8E90, int, 0, "SR_ShardManager", (int)hInstance, (int)lpCmdLine, 1, 0);
}

void CShardManager::Initialize()
{
    // Hook LogWriter first
    CAppLogger::SetupHook(0x009D8090);

    // Other hooks
    SharManager::CMainProcess::SetupHook();

    // CShardManager vftable hooks
    MEMUTIL_VFTABLE_HOOK(0x00B560EC,  1, &CShardManager::init_module);
    MEMUTIL_VFTABLE_HOOK(0x00B560EC, 11, &CShardManager::init_localdata);

    // WinMain hook
    MEMUTIL_REPLACE_OFFSET(0x00A531D8, &ShardManager_WinMain);

    //////////////////////////////////////////////////////////////////
    // Static Patches

    MEMUTIL_WRITE_VALUE(BYTE, 0x0075EB1B + 1, (BYTE)0xC8); //MOB_THIEF
    MEMUTIL_WRITE_VALUE(BYTE, 0x0075EC2F + 2, (BYTE)0xC7); //MOB_THIEF

    MEMUTIL_WRITE_VALUE(BYTE, 0x0075ED3B + 1, (BYTE)0xC8); //MOB_HUNTER
    MEMUTIL_WRITE_VALUE(BYTE, 0x0075EE4F + 2, (BYTE)0xC7); //MOB_HUNTER

    MEMUTIL_WRITE_VALUE(BYTE, 0x00759D4F + 1, (BYTE)0xC8); //UNK
    MEMUTIL_WRITE_VALUE(BYTE, 0x00759E75 + 2, (BYTE)0xC8); //UNK

    MEMUTIL_WRITE_VALUE(BYTE, 0x0072E217 + 1, (BYTE)0xC8); //UNK

    MEMUTIL_WRITE_VALUE(BYTE, 0x0074201C + 1, (BYTE)0xC8); //MERCENARY
    MEMUTIL_WRITE_VALUE(BYTE, 0x007421EF + 1, (BYTE)0xC8); //SIEGEGUARD

    // schdule define change
    const char* SCHEDEF_RECORD_ACTIVEUSER = "SCHEDULE_DEF_RECORD_ACTIVEUSER"; //SCHEDEF_RECORD_ACTIVEUSER
    MEMUTIL_REPLACE_ADDRESS(0x009AFCA7 + 1, (uintptr_t)SCHEDEF_RECORD_ACTIVEUSER);
}

BOOL CShardManager::init_module()
{
    if (!HydraFramework::CMainProcess::CreateInstance(this, "SharManager")) {
        PutLog(FATAL, "Failed to initialize Hydra");
        return FALSE;
    }

    if (!CDbManager::CreateInstance(10, 20)) {
        PutLog(FATAL, "Failed to create database instance.");
        return FALSE;
    }

    return reinterpret_thiscall(0x009EFE90, BOOL, this);
}

BOOL CShardManager::init_localdata()
{
    if (!g_pHydraMainProcess) {
        PutLog(FATAL, "Failed to initialize Hydra");
        return FALSE;
    }

    if (!g_pDbMgr) {
        PutLog(FATAL, "Failed to initialize DbManager");
        return FALSE;
    } else {
        const std::string& database = "Database.ini";

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
    }

    return reinterpret_thiscall(0x0059F910, BOOL, this);
}
