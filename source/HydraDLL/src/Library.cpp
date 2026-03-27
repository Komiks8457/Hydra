#include "Library.h"
#include "utils/MemoryUtility.h"
#include "utils/ConfigParser.h"
#include "stdext.h"

#include "AgentServer.h"
#include "DownloadServer.h"
#include "FarmManager.h"
#include "GatewayServer.h"
#include "GlobalManager.h"
#include "MachineManager.h"
#include "GameServer.h"
#include "ShardManager.h"
#include "StaticPatches.h"
#include "version.h"

// Globals
WCHAR szFullPath[MAX_PATH];
WCHAR szFileName[MAX_PATH];
WCHAR szFileExtn[MAX_PATH];

// Structure to hold EXE-specific settings
struct HydraModuleEntry {
    const wchar_t* exeName;
    const wchar_t* iniPath;
    const wchar_t* dllPath;
    void (*specialPatches)(); // Function pointer for unique patches
};

// --- Special Patch Functions ---

void PatchAgentServer() {
    CStaticPatches::AgentServerCertPatch();
    CAgentServer::Initialize();
}

void PatchDownloadServer() {
    CStaticPatches::DownloadServerCertPatch();
    CDownloadServer::Initialize();
}

void PatchFarmManager() {
    CStaticPatches::FarmManagerCertPatch();
    CFarmManager::Initialize();
}

void PatchGatewayServer() {
    CStaticPatches::GatewayServerCertPatch();
    CGatewayServer::Initialize();
}

void PatchGlobalManager() {
    CStaticPatches::GlobalManagerCertPatch();
    CGlobalManager::Initialize();
}

void PatchMachineManager() {
    CStaticPatches::MachineManagerCertPatch();
    CMachineManager::Initialize();
}

void PatchGameServer() {
    CStaticPatches::GameServerCertPatch();
    CGameServer::Initialize();
}

void PatchSharManager() {
    CStaticPatches::ShardManagerCertPatch();
    CShardManager::Initialize();
}

void PatchSMC() {
    MEMUTIL_WRITE_VALUE(BYTE, 0x004288A2, 0xEB);
}

// --- Configuration Table ---
// Add new modules here to support them automatically
static const HydraModuleEntry g_ModuleTable[] = {
    { L"agentserver.exe",     L".\\Vanguard\\AgentServer.ini",    L".\\Vanguard\\AgentServer.dll",    PatchAgentServer },
    { L"downloadserver.exe",  L".\\Vanguard\\DownloadServer.ini", L".\\Vanguard\\DownloadServer.dll", PatchDownloadServer },
    { L"farmmanager.exe",     L".\\Vanguard\\FarmManager.ini",    L".\\Vanguard\\FarmManager.dll",    PatchFarmManager },
    { L"gatewayserver.exe",   L".\\Vanguard\\GatewayServer.ini",  L".\\Vanguard\\GatewayServer.dll",  PatchGatewayServer },
    { L"globalmanager.exe",   L".\\Vanguard\\GlobalManager.ini",  L".\\Vanguard\\GlobalManager.dll",  PatchGlobalManager },
    { L"machinemanager.exe",  L".\\Vanguard\\MachineManager.ini", L".\\Vanguard\\MachineManager.dll", PatchMachineManager },
    { L"gameserver.exe",      L".\\Vanguard\\GameServer.ini",     L".\\Vanguard\\GameServer.dll",     PatchGameServer },
    { L"shardmanager.exe",    L".\\Vanguard\\ShardManager.ini",   L".\\Vanguard\\ShardManager.dll",   PatchSharManager },
    { L"smc.exe",             L".\\Vanguard\\SMC.ini",            L".\\Vanguard\\SMC.dll",            PatchSMC }
};

void DisableConsoleSelect()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prev_mode;

    if (GetConsoleMode(hInput, &prev_mode))
    {
        DWORD new_mode = prev_mode & ~(0x0040 | 0x0020);

        new_mode |= 0x0080;

        SetConsoleMode(hInput, new_mode);
    }
}

void ShowConsole(bool showConsole, const char* name)
{
    char fullBuffer[256];
    _snprintf(fullBuffer, sizeof(fullBuffer), "%s - HydraFramework (%s)",
              name ? name : "Unknown", BUILD_REVISION_STRING);

    if (showConsole)
    {
        if (AllocConsole())
        {
            SetConsoleTitleA(fullBuffer);
            SetConsoleOutputCP(65001);
            DisableConsoleSelect();

            freopen("CONOUT$", "w+", stdout);
        }

        const int TOTAL_WIDTH = 89;

        std::string displayStr = fullBuffer;
        int displayLen = (int)displayStr.length();

        // 2. Calculate padding for the center line
        // TotalWidth - 2 (╠ and ╣) - 2 (Spaces) - displayLen
        int totalInnerEquals = TOTAL_WIDTH - 2 - 2 - displayLen;
        if (totalInnerEquals < 0) totalInnerEquals = 0;

        int leftEquals = totalInnerEquals / 2;
        int rightEquals = totalInnerEquals - leftEquals;

        // 3. Build Top/Bottom Borders (Must be same width as TOTAL_WIDTH)
        std::string topBorder = "╔";
        std::string bottomBorder = "╚";
        for(int i = 0; i < (TOTAL_WIDTH - 2); ++i) {
            topBorder += "═";
            bottomBorder += "═";
        }
        topBorder += "╗";
        bottomBorder += "╝";

        // 4. Build the Centered Line
        std::string centeredLine = "╠";
        for(int i = 0; i < leftEquals; ++i) centeredLine += "═";
        centeredLine += " ";
        centeredLine += displayStr;
        centeredLine += " ";
        for(int i = 0; i < rightEquals; ++i) centeredLine += "═";
        centeredLine += "╣";

        // 5. Output
        Logger::info("%s", topBorder.c_str());
        Logger::info("%s", centeredLine.c_str());
        Logger::info("%s", bottomBorder.c_str());
    }
}

void CLibrary::DoSomeWork()
{
    HANDLE hProcess = GetCurrentProcess();
    GetModuleFileNameW(NULL, szFullPath, MAX_PATH);
    _wsplitpath(szFullPath, NULL, NULL, szFileName, szFileExtn);

    __inifile vanguard;
    __cfgfile serverConfig;

    const std::string& configFile = (__stringw(szFileName).equal(L"smc") ? ".\\ServiceManager.cfg" : ".\\Server.cfg");

    if (!serverConfig.Load(configFile)) {
        char err[256];
        _snprintf(err, 256, "Cannot find \"%s\", contact administrator.", configFile.c_str());
        MessageBoxA(NULL, err, "Hydra", MB_ICONERROR | MB_OK);
        TerminateProcess(hProcess, EXIT_FAILURE);
        return;
    }

    const std::string& extension = serverConfig.GetString(__tostra(szFileName), "Extension");
    bool console = serverConfig.GetBool(__tostra(szFileName), "ShowConsole");

    // --- Core Logic: Loop through the table ---
    int numModules = sizeof(g_ModuleTable) / sizeof(HydraModuleEntry);
    for (int i = 0; i < numModules; ++i)
    {
        if (__stringw(szFullPath).endswith(g_ModuleTable[i].exeName))
        {
            ShowConsole(console, __tostra(szFileName).c_str());

            // 2. Run Special patches (like SMC or GlobalManager)
            if (g_ModuleTable[i].specialPatches)
                g_ModuleTable[i].specialPatches();

            // 3. Load Vanguard
            if (vanguard.load(g_ModuleTable[i].iniPath) && __chkfile(g_ModuleTable[i].dllPath).exists()) {
                if (!LoadLibraryW(g_ModuleTable[i].dllPath)) {
                    MessageBoxW(NULL, g_ModuleTable[i].dllPath, L"Failed to load Vanguard",
                                MB_ICONERROR | MB_OK);
                    TerminateProcess(hProcess, EXIT_FAILURE);
                    return;
                }
            }

            // 4. Load Addons (Common logic for all)
            if (__stringa(extension).endswith(".dll") && __chkfile(extension).exists()) {
                if (!LoadLibraryA(extension.c_str())) {
                    MessageBoxA(NULL, extension.c_str(), "Failed to load Extension",
                                MB_ICONERROR | MB_OK);
                    TerminateProcess(hProcess, EXIT_FAILURE);
                    return;
                }
            }

            return;
        }
    }
}
