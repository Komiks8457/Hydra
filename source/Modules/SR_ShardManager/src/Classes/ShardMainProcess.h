#ifndef SHARDMANAGERMAINPROCESS_H
#define SHARDMANAGERMAINPROCESS_H

#include "BSLib/NetEngine/Msg.h"

namespace SharManager
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
