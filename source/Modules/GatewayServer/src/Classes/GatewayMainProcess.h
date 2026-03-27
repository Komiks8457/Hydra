#ifndef GATEWAYMAINPROCESS_H
#define GATEWAYMAINPROCESS_H

#include "BSLib/NetEngine/Msg.h"

class CMassiveMsg;
class CGatewayMainProcess {
public:
    static void SetupHook();

private:
    UINT32 HandleMsg(CMsg *pMsg, DWORD dwOverlappedID, LPVOID lpParam, CMassiveMsg *pMassiveMsg);
};


#endif
