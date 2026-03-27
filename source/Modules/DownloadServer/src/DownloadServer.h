#ifndef DOWNLOADSERVER_H
#define DOWNLOADSERVER_H

#include "pch.h"

class CDownloadServer {
public:
    static void Initialize();

private:
    BOOL init_module();
    BOOL init_localdata();
};

extern CDownloadServer* g_pDownloadServer;

#endif
