#include "GameMainProcess.h"
#include "utils/MemoryUtility.h"

namespace GameServer
{
    void CMainProcess::SetupHook() {
        MEMUTIL_VFTABLE_HOOK(0x00DAFF34, 9, &CMainProcess::HandleMsg);
    }

    UINT32 CMainProcess::HandleMsg(CMsg *pMsg, DWORD dwOverlappedID, LPVOID lpParam, CMassiveMsg *pMassiveMsg) {
        return reinterpret_thiscall(0x00BDFC10, UINT32, this, pMsg, dwOverlappedID, lpParam, pMassiveMsg);
    }
}
