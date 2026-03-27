#include "NetEngine.h"
#include "BSLib/AppLogger.h"
#include "utils/MemoryUtility.h"

CNetEngine* g_pNetEngine = NULL;
DWORD dwNetEngineClassEntry = NULL;

bool CNetEngine::Initialize(DWORD ptr)
{
    if (ptr == 0) return false;

    if (g_pNetEngine) return true;

    g_pNetEngine = reinterpret_cast<CNetEngine*>(ptr);

    dwNetEngineClassEntry = (DWORD)*(CNetEngine**)g_pNetEngine;

    //MEMUTIL_VFTABLE_HOOK(dwNetEngineClass, 22, &CNetEngine::sub_C0B610);

    return true;
}

CMsg* CNetEngine::NewMsg_IMPL(WORD wMsgID, bool IsEncrypted)
{
    if (!dwNetEngineClassEntry)
        return NULL;

    DWORD dwVFTableAddress = MEMUTIL_VFTABLE_GET_FUNC(dwNetEngineClassEntry, 18);
    CMsg *pMsg = reinterpret_stdcall(dwVFTableAddress, CMsg*, this, IsEncrypted);
    pMsg->SetMsgID(wMsgID);
    return pMsg;
}

CMsg* CNetEngine::NewMsgFrom_IMPL(WORD wMsgID, const char *szFile, int nLine, const char *szFnName, bool IsEncrypted)
{
    if (!dwNetEngineClassEntry)
        return NULL;

    DWORD dwVFTableAddress = MEMUTIL_VFTABLE_GET_FUNC(dwNetEngineClassEntry, 19);
    CMsg *pMsg = reinterpret_stdcall(dwVFTableAddress, CMsg*, this, szFile, nLine, szFnName, IsEncrypted);
    pMsg->SetMsgID(wMsgID);
    return pMsg;
}

void CNetEngine::DelMsg_IMPL(CMsg *pMsg)
{
    if (!dwNetEngineClassEntry)
        return;

    DWORD dwVFTableAddress = MEMUTIL_VFTABLE_GET_FUNC(dwNetEngineClassEntry, 20);
    reinterpret_stdcall(dwVFTableAddress, void, this, pMsg);
}

IBSNet::NERR CNetEngine::SendMsg_IMPL(DWORD dwSessionID, CMsg *pMsg)
{
    if (!dwNetEngineClassEntry)
        return NERR_UNKNOWN;

    DWORD dwVFTableAddress = MEMUTIL_VFTABLE_GET_FUNC(dwNetEngineClassEntry, 22);
    return reinterpret_stdcall(dwVFTableAddress, IBSNet::NERR, this, dwSessionID, pMsg);
}
