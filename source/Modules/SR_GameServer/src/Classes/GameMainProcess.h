#ifndef GAMESERVERMAINPROCESS_H
#define GAMESERVERMAINPROCESS_H

#include "BSLib/NetEngine/Msg.h"

namespace GameServer
{
    class CMassiveMsg;
    class CMainProcess {
    public:
        static void SetupHook();

    private:
        UINT32 HandleMsg(CMsg *pMsg, DWORD dwOverlappedID, LPVOID lpParam, CMassiveMsg *pMassiveMsg);
    };
}

#endif
