#ifndef AGENTMAINPROCESS_H
#define AGENTMAINPROCESS_H

#include "BSLib/NetEngine/Msg.h"

class CMassiveMsg;
class CAgentMainProcess {
public:
    static void SetupHook();

private:
    UINT32 HandleMsg(CMsg *pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg *pMassiveMsg);
};

#endif
