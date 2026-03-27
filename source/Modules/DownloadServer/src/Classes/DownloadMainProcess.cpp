#include "DownloadMainProcess.h"
#include "utils/MemoryUtility.h"

void CDownloadServerMainProcess::SetupHook() {
    MEMUTIL_VFTABLE_HOOK(0x0151AAF4, 9, &CDownloadServerMainProcess::HandleMsg);
}

UINT32 CDownloadServerMainProcess::HandleMsg(CMsg *pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg *pMassiveMsg)
{
    return reinterpret_thiscall(0x014486E0, UINT32, this, pMsg, dwOverlappedJobID, lpParam, pMassiveMsg);
}
