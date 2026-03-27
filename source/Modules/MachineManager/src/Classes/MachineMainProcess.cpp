#include "MachineMainProcess.h"
#include "utils/MemoryUtility.h"

void CMachineManagerMainProcess::SetupHook() {
    MEMUTIL_VFTABLE_HOOK(0x015650E4, 9, &CMachineManagerMainProcess::HandleMsg);
}

UINT32 CMachineManagerMainProcess::HandleMsg(CMsg *pMsg, DWORD dwOverlappedID, void *lpParam, CMassiveMsg *pMassiveMsg) {
    return reinterpret_thiscall(0x01491B40, UINT32, this, pMsg, dwOverlappedID, lpParam, pMassiveMsg);
}
