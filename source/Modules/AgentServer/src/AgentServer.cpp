#include "AgentServer.h"
#include "BSLib/AppLogger.h"
#include "BSLib/HydraFramework.h"
#include "utils/MemoryUtility.h"
#include "Classes/AgentMainProcess.h"

CAgentServer* g_pAgentServer = NULL;

int AgentServer_WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    //dword_5A30D8 = (int)&dword_5923F8;
    MEMUTIL_WRITE_VALUE(uintptr_t, 0x005A30D8, 0x005923F8);

    //assign our g_pAgentServer global pointer
    g_pAgentServer = *(CAgentServer**)0x005A30D8; // or (CAgentServer*)0x005923F8;

    Logger::warn2("g_pAgentServer = CAgentServer Instance (0x%p)", g_pAgentServer);

    //return sub_466CB0(0, (CHAR *)"AgentServer", hInstance, (int)lpCmdLine, 1, 0);
    return reinterpret_cdecl(0x00466CB0, int, 0, "AgentServer", hInstance, (int)lpCmdLine, 1, 0);
}

void CAgentServer::Initialize()
{
    // Hook LogWriter first
    CAppLogger::SetupHook(0x00464DD0);

    // Other hooks
    CAgentMainProcess::SetupHook();

    // CAgentServer vftable hooks
    MEMUTIL_VFTABLE_HOOK(0x0051B684,  1, &CAgentServer::init_module);
    MEMUTIL_VFTABLE_HOOK(0x0051B684, 11, &CAgentServer::init_localdata);

    // WinMain hook
    MEMUTIL_REPLACE_OFFSET(0x004DE08B, &AgentServer_WinMain);
}

BOOL CAgentServer::init_module()
{
    HydraFramework::CMainProcess::CreateInstance(this, "AgentServer");

    if (!g_pHydraMainProcess) {
        PutLog(FATAL, "Failed to initialize Hydra");
        return FALSE;
    }

    return reinterpret_thiscall(0x0046DB40, BOOL, this);
}

BOOL CAgentServer::init_localdata()
{
    if (!reinterpret_thiscall(0x004291D0, BOOL, this))
        return FALSE;

    if (!g_pHydraMainProcess) {
        PutLog(FATAL, "Failed to initialize Hydra");
        return FALSE;
    }

    return TRUE;
}
