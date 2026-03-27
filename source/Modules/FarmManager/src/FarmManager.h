#ifndef FARMMANAGER_H
#define FARMMANAGER_H

#include "pch.h"

class CFarmManager {
public:
    static void Initialize();
    uint8_t GetServerBodyID(const char *moduleName);

private:
    BOOL init_module();
    BOOL init_localdata();

};

extern CFarmManager* g_pFarmManager;

#endif
