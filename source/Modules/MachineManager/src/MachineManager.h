#ifndef MACHINEMANAGER_H
#define MACHINEMANAGER_H

#include "pch.h"

class CMachineManager {
public:
    static void Initialize();

private:
    BOOL init_module();
    BOOL init_localdata();
};

extern CMachineManager *g_pMachineManager;

#endif
