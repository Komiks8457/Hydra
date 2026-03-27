#ifndef SHARDMANAGER_H
#define SHARDMANAGER_H

#include "pch.h"

class CShardManager {
public:
    static void Initialize();

private:
    BOOL init_module();
    BOOL init_localdata();
};

extern CShardManager *g_pShardManager;

#endif
