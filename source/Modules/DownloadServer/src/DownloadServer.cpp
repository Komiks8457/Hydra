#include "DownloadServer.h"
#include "BSLib/AppLogger.h"
#include "BSLib/HydraFramework.h"
#include "utils/MemoryUtility.h"
#include "Classes/DownloadMainProcess.h"

CDownloadServer* g_pDownloadServer = NULL;

int DownloadServer_WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    //dword_1561078 = (int)&unk_153FEC8;
    MEMUTIL_WRITE_VALUE(uintptr_t, 0x01561078, 0x0153FEC8);

    //assign our g_pDownloadServer global pointer
    g_pDownloadServer = *(CDownloadServer**)0x01561078; // or (CDownloadServer*)0x0153FEC8;

    Logger::warn2("g_pDownloadServer = CDownloadServer Instance (0x%p)", g_pDownloadServer);

    //return sub_14507F0(0, "DownloadServer", (int)hInstance, (int)lpCmdLine, 1, 0);
    return reinterpret_cdecl(0x014507F0, int, 0, "DownloadServer", hInstance, (int)lpCmdLine, 1, 0);
}

void CDownloadServer::Initialize()
{
    // Hook LogWriter first
    CAppLogger::SetupHook(0x0144E910);

    // Other hooks
    CDownloadServerMainProcess::SetupHook();

    // CDownloadServer vftable hooks
    MEMUTIL_VFTABLE_HOOK(0x0151AE84,  1, &CDownloadServer::init_module);
    MEMUTIL_VFTABLE_HOOK(0x0151AE84, 11, &CDownloadServer::init_localdata);

    // WinMain hook
    MEMUTIL_REPLACE_OFFSET(0x014E2644, &DownloadServer_WinMain);
}

BOOL CDownloadServer::init_module()
{
    HydraFramework::CMainProcess::CreateInstance(this, "DownloadServer");

    if (!g_pHydraMainProcess) {
        PutLog(FATAL, "Failed to initialize Hydra");
        return FALSE;
    }

    return reinterpret_thiscall(0x0144BC50, BOOL, this);
}

BOOL CDownloadServer::init_localdata()
{
    if(!reinterpret_thiscall(0x01435C80, BOOL, this))
        return FALSE;

    if (!g_pHydraMainProcess) {
        PutLog(FATAL, "Failed to initialize Hydra");
        return FALSE;
    }

    return TRUE;
}
