#ifndef AGENTSERVER_H
#define AGENTSERVER_H

#include "pch.h"

class CAgentServer {
public:
    static void Initialize();

private:
    BOOL init_module();
    BOOL init_localdata();
};

extern CAgentServer* g_pAgentServer;

#endif
