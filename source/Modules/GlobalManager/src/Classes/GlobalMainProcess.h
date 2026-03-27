#ifndef GLOBALMAINPROCESS_H
#define GLOBALMAINPROCESS_H

#include "BSLib/NetEngine/Msg.h"

class CMassiveMsg;
class CGlobalMainProcess {
public:
    static void SetupHook();

private:
    int64_t  RegisterMsgHandler();
    int32_t  HandleMsg(CMsg *pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg *pMassiveMsg);
    void     SendMsgToServerBodyDirectly(CMsg *pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg *pMassiveMsg);
    int*     OnENM_SESSION_LOST(CMsg *pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg *pMassiveMsg);
};

#endif
