#ifndef FARMMANAGERMAINPROCESS_H
#define FARMMANAGERMAINPROCESS_H

#include "BSLib/NetEngine/Msg.h"

class CMassiveMsg;
class CFarmManagerMainProcess {
public:
    static void SetupHook();
    uint8_t  GetServerBodyID(const char *moduleName);

private:
    int32_t  RegisterMsgHandler();
    uint32_t HandleMsg(CMsg *pMsg, DWORD dwOverlappedID, LPVOID lpParam, CMassiveMsg *pMassiveMsg);
};

#endif
