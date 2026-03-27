#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "pch.h"
#include "BSLib/NetEngine/Msg.h"

class CGameServer {
public:
    static void Initialize();
    CMsg *AllocMsgToBroadcast(WORD wMsgID);

private:
    BOOL init_module();
    BOOL init_localdata();
};

extern CGameServer *g_pGameServer;

#endif
