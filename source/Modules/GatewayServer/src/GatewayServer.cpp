#include "GatewayServer.h"
#include "BSLib/AppLogger.h"
#include "HydraFramework.h"
#include "utils/MemoryUtility.h"
#include "Classes/GatewayMainProcess.h"

CGatewayServer* g_pGatewayServer = NULL;

int GatewayServer_WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    //dword_15D29F0 = (int)&unk_15B1BE0;
    MEMUTIL_WRITE_VALUE(uintptr_t, 0x015D29F0, 0x015B1BE0);

    //assign our g_pFarmManager global pointer
    g_pGatewayServer = *(CGatewayServer**)0x015D29F0; // or (CGatewayServer*)0x015B1BE0;

    Logger::warn2("g_pGatewayServer = CGatewayServer Instance (0x%p)", g_pGatewayServer);

    //return sub_1495B30(0, "GatewayServer", (int)hInstance, (int)lpCmdLine, 1, 0);
    return reinterpret_cdecl(0x01495B30, int, 0, "GatewayServer", hInstance, (int)lpCmdLine, 1, 0);
}

void CGatewayServer::Initialize()
{
    // Hook LogWriter first
    CAppLogger::SetupHook(0x01493C50);

    // Other hooks
    CGatewayMainProcess::SetupHook();

    // CFarmManager vftable hooks
    MEMUTIL_VFTABLE_HOOK(0x015815FC,  1, &CGatewayServer::init_module);
    MEMUTIL_VFTABLE_HOOK(0x015815FC, 11, &CGatewayServer::init_localdata);

    // WinMain hook
    MEMUTIL_REPLACE_OFFSET(0x0154139C, &GatewayServer_WinMain);
}

BOOL CGatewayServer::init_module()
{
    HydraFramework::CMainProcess::CreateInstance(this, "GatewayServer");

    if (!g_pHydraMainProcess) {
        PutLog(FATAL, "Failed to initialize Hydra");
        return FALSE;
    }

    MEMUTIL_WRITE_POINTER(0x015826C0, GlobalData::SecretKey, sizeof(GlobalData::SecretKey));

    return reinterpret_thiscall(0x014CBD00, BOOL, this);
}

BOOL CGatewayServer::init_localdata()
{
    if (!reinterpret_thiscall(0x01465A10, BOOL, this))
        return FALSE;

    if (!g_pHydraMainProcess) {
        PutLog(FATAL, "Failed to initialize Hydra");
        return FALSE;
    }

    Logger::info2("New secret key applied: \"%s\"", (const char*)0x015826C0);

    return TRUE;
}
