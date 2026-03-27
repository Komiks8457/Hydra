#ifndef GATEWAYSERVER_H
#define GATEWAYSERVER_H

#include "pch.h"

class CGatewayServer {
public:
    static void Initialize();

private:
    BOOL init_module();
    BOOL init_localdata();

};

extern CGatewayServer* g_pGatewayServer;

#endif
