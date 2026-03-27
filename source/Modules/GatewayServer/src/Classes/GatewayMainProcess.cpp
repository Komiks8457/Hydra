#include "GatewayMainProcess.h"
#include "utils/MemoryUtility.h"

void CGatewayMainProcess::SetupHook() {
    MEMUTIL_VFTABLE_HOOK(0x01580C4C, 9, &CGatewayMainProcess::HandleMsg);
}

UINT32 CGatewayMainProcess::HandleMsg(CMsg *pMsg, DWORD dwOverlappedID, LPVOID lpParam, CMassiveMsg *pMassiveMsg) {
    return reinterpret_thiscall(0x0145DBE0, UINT32, this, pMsg, dwOverlappedID, lpParam, pMassiveMsg);
}
