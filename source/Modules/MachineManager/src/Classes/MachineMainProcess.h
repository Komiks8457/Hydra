#ifndef MACHINEMANAGERMAINPROCESS_H
#define MACHINEMANAGERMAINPROCESS_H

#include "BSLib/NetEngine/Msg.h"

class CMassiveMsg;
class CMachineManagerMainProcess {
public:
    static void SetupHook();

private:
    UINT32 HandleMsg(CMsg *pMsg, DWORD dwOverlappedID, void *lpParam, CMassiveMsg *pMassiveMsg);
};


#endif
