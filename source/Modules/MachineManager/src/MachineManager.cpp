#include "MachineManager.h"
#include "BSLib/AppLogger.h"
#include "BSLib/HydraFramework.h"
#include "utils/MemoryUtility.h"
#include "Classes/MachineMainProcess.h"

CMachineManager *g_pMachineManager = NULL;

int MachineManager_WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    //dword_15AD5B8 = (int)&dword_158C008;
    MEMUTIL_WRITE_VALUE(uintptr_t, 0x015AD5B8, 0x0158C008);

    //assign our g_pGlobalManager global pointer
    g_pMachineManager = *(CMachineManager**)0x015AD5B8; // or (CMachineManager*)0x0158C008;

    Logger::warn2("g_pMachineManager = CMachineManager Instance (0x%p)", g_pMachineManager);

    //return sub_14904E0(2, "MachineManager", hInstance, (int)lpCmdLine, 1, 1);
    return reinterpret_cdecl(0x014904E0, int, 2, "MachineManager", (int)hInstance, (int)lpCmdLine, 1, 1);
}

void CMachineManager::Initialize()
{
    // Hook LogWriter first
    CAppLogger::SetupHook(0x0148E600);

    // Other hooks
    CMachineManagerMainProcess::SetupHook();

    // CMachineManager vftable hooks
    MEMUTIL_VFTABLE_HOOK(0x01564B24,  1, &CMachineManager::init_module);
    MEMUTIL_VFTABLE_HOOK(0x01564B24, 11, &CMachineManager::init_localdata);

    // WinMain hook
    MEMUTIL_REPLACE_OFFSET(0x0152AE42, &MachineManager_WinMain);
}

BOOL CMachineManager::init_module()
{
    HydraFramework::CMainProcess::CreateInstance(this, "MachineManager");

    if (!g_pHydraMainProcess) {
        PutLog(FATAL, "Failed to initialize Hydra");
        return FALSE;
    }

    return reinterpret_thiscall(0x0148B900, BOOL, this);
}

BOOL CMachineManager::init_localdata()
{
    if (!reinterpret_thiscall(0x01471130, BOOL, this))
        return FALSE;

    if (!g_pHydraMainProcess) {
        PutLog(FATAL, "Failed to initialize Hydra");
        return FALSE;
    }

    return TRUE;
}
