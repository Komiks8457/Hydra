#include "AgentMainProcess.h"
#include "utils/MemoryUtility.h"

void CAgentMainProcess::SetupHook() {
    MEMUTIL_VFTABLE_HOOK(0x0051B4E4, 9, &CAgentMainProcess::HandleMsg);
}

UINT32 CAgentMainProcess::HandleMsg(CMsg *pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg *pMassiveMsg)
{
    return reinterpret_thiscall(0x00428830, UINT32, this, pMsg, dwOverlappedJobID, lpParam, pMassiveMsg);
}
