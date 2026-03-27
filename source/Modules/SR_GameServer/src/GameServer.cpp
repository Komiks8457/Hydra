#include "GameServer.h"
#include "BSLib/AppLogger.h"
#include "BSLib/HydraFramework.h"
#include "BSLib/Database/DbManager.h"
#include "utils/MemoryUtility.h"
#include "Classes/GameMainProcess.h"
#include "Classes/GameObjects/GObjPC.h"

CGameServer *g_pGameServer = NULL;

int GameServer_WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    // dword_10F6910 = (int)&dword_101EFF0
    MEMUTIL_WRITE_VALUE(uintptr_t, 0x010F6910, 0x0101EFF0);

    // assign our g_pGlobalManager global pointer
    g_pGameServer = *(CGameServer**)0x010F6910; // or (CGameServer*)0x0101EFF0;

    Logger::warn2("g_pGameServer = CGameServer (0x%p)", g_pGameServer);

    // return sub_BCB7A0(0, "SR_GameServer", (int)hInstance, (int)lpCmdLine, 1, 0);
    return reinterpret_cdecl(0x00BCB7A0, int, 0, "SR_GameServer", (int)hInstance, (int)lpCmdLine, 1, 0);
}

void CGameServer::Initialize()
{
    //////////////////////////////////////////////////////////////////
    // Hook LogWriter first

    CAppLogger::SetupHook(0x00BCA8A0);

    //////////////////////////////////////////////////////////////////
    // Other hooks

    GameServer::CMainProcess::SetupHook();
    CGObjPC::SetupHook();

    //////////////////////////////////////////////////////////////////
    // CGameServer vftable hooks

    MEMUTIL_VFTABLE_HOOK(0x00DAFA04,  1, &CGameServer::init_module);
    MEMUTIL_VFTABLE_HOOK(0x00DAFA04, 11, &CGameServer::init_localdata);

    // WinMain hook
    MEMUTIL_REPLACE_OFFSET(0x00C764C7, &GameServer_WinMain);

    //////////////////////////////////////////////////////////////////
    // Static Patches

    MEMUTIL_WRITE_VALUE(BYTE, 0x00902673 + 1, (BYTE)0xC8); //MOB_THIEF
    MEMUTIL_WRITE_VALUE(BYTE, 0x00902787 + 2, (BYTE)0xC7); //MOB_THIEF

    MEMUTIL_WRITE_VALUE(BYTE, 0x009028A3 + 1, (BYTE)0xC8); //MOB_HUNTER
    MEMUTIL_WRITE_VALUE(BYTE, 0x009029B7 + 2, (BYTE)0xC7); //MOB_HUNTER

    MEMUTIL_WRITE_VALUE(BYTE, 0x008FDC70 + 1, (BYTE)0xC8); //UNK
    MEMUTIL_WRITE_VALUE(BYTE, 0x008FDD95 + 2, (BYTE)0xC8); //UNK

    MEMUTIL_WRITE_VALUE(BYTE, 0x008D4C56 + 1, (BYTE)0xC8); //UNK

    MEMUTIL_WRITE_VALUE(BYTE, 0x008E77F1 + 1, (BYTE)0xC8); //MERCENARY
    MEMUTIL_WRITE_VALUE(BYTE, 0x008E79D4 + 1, (BYTE)0xC8); //SEIGEGUARD
}

BOOL CGameServer::init_module()
{
    if (!HydraFramework::CMainProcess::CreateInstance(this, "GameServer")) {
        PutLog(FATAL, "Failed to initialize Hydra");
        return FALSE;
    }

    if (!CDbManager::CreateInstance(10, 20)) {
        PutLog(FATAL, "Failed to create database instance.");
        return FALSE;
    }

    return reinterpret_thiscall(0x00BC87E0, BOOL, this);
}

BOOL CGameServer::init_localdata()
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

    return reinterpret_thiscall(0x00481680, BOOL, this);
}

CMsg* CGameServer::AllocMsgToBroadcast(WORD wMsgID)
{
    //int __cdecl sub_4C8A10(__int16 a1)
    return reinterpret_cdecl(0x004C8A10, CMsg*, wMsgID);
}
