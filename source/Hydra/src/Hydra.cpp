#include "Library.h"
#include "utils/MemoryUtility.h"

BOOL g_HydraInitialized = FALSE;

void TriggerHydraInit()
{
    if (g_HydraInitialized)
        return;
    g_HydraInitialized = TRUE;
    CLibrary::DoSomeWork();
}

typedef LPSTR (WINAPI *PGET_COMMAND_LINE_A)(VOID);
PGET_COMMAND_LINE_A TrueGetCommandLineA = GetCommandLineA;
LPSTR WINAPI MyGetCommandLineA(VOID)
{
    if (!g_HydraInitialized)
        TriggerHydraInit();
    return TrueGetCommandLineA();
}

typedef LPWSTR (WINAPI *PGET_COMMAND_LINE_W)(VOID);
PGET_COMMAND_LINE_W TrueGetCommandLineW = GetCommandLineW;
LPWSTR WINAPI MyGetCommandLineW(VOID)
{
    if (!g_HydraInitialized)
        TriggerHydraInit();
    return TrueGetCommandLineW();
}

typedef BOOL (WINAPI *PALLOC_CONSOLE)(VOID);
PALLOC_CONSOLE TrueAllocConsole = AllocConsole;
BOOL WINAPI MyAllocConsole(VOID)
{
    void* callerAddress = _ReturnAddress();
    HMODULE hCallerModule = NULL;

    if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                           GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                           (LPCSTR)callerAddress,
                           &hCallerModule))
    {
        HMODULE hMyDll = GetModuleHandleA("Hydra.dll");
        if (hCallerModule == hMyDll)
            return TrueAllocConsole();
    }

    SetLastError(ERROR_ACCESS_DENIED);
    return FALSE;
}

BOOL APIENTRY DllMain(HMODULE hInst, const DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hInst);
            MEMUTIL_HOOK_FN(TrueGetCommandLineA, MyGetCommandLineA)
            MEMUTIL_HOOK_FN(TrueGetCommandLineW, MyGetCommandLineW)
            MEMUTIL_HOOK_FN(TrueAllocConsole, MyAllocConsole)
            break;

        case DLL_PROCESS_DETACH:
            if (lpReserved == NULL)
            {
                MEMUTIL_UNHOOK(TrueGetCommandLineA, MyGetCommandLineA)
                MEMUTIL_UNHOOK(TrueGetCommandLineW, MyGetCommandLineW)
                MEMUTIL_UNHOOK(TrueAllocConsole, MyAllocConsole)
            }
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        default: break;
    }
    return TRUE;
}