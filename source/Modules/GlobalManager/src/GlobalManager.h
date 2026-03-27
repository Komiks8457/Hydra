#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H

#include "pch.h"
#include "BSLib/NetEngine/Msg.h"

class CGlobalManager {
public:
    static void Initialize();
    static HWND GetWinHandle();
    uint8_t GetServerBodyID(const char *moduleName);

private:
    BOOL init_module();
    BOOL init_localdata();
};

extern CGlobalManager *g_pGlobalManager;

#endif
