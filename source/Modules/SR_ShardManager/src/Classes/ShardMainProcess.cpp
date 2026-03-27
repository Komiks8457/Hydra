#include "ShardMainProcess.h"
#include "utils/MemoryUtility.h"

namespace SharManager
{
    void CMainProcess::SetupHook()
    {
        MEMUTIL_VFTABLE_HOOK(0x00B59EB4, 9, &CMainProcess::HandleMsg);
    }

    UINT32 CMainProcess::HandleMsg(CMsg *pMsg, DWORD dwOverlappedID, LPVOID lpParam, CMassiveMsg *pMassiveMsg)
    {
        return reinterpret_thiscall(0x009EBF10, UINT32, this, pMsg, dwOverlappedID, lpParam, pMassiveMsg);
    }
}
