#include "GlobalMainProcess.h"
#include "utils/MemoryUtility.h"
#include "HydraFramework.h"
#include "BSLib/AppLogger.h"
#include "BSLib/NetEngine/NetEngine.h"

typedef void (__thiscall* tRegisterPacket)(void* pThis, unsigned short opcode, void* handlerProc);

int __cdecl CustomMsgHandler(CMsg *pMsg)
{
    if (g_pHydraMainProcess && pMsg)
        g_pHydraMainProcess->HandleCustomMsg(pMsg);

    DELMSG(pMsg);
    pMsg = NULL;
    return 1;
}

void CGlobalMainProcess::SetupHook()
{
    //MEMUTIL_VFTABLE_HOOK(0x018053CC,  1, &CGlobalMainProcess::Init);
    MEMUTIL_VFTABLE_HOOK(0x018053CC,  7, &CGlobalMainProcess::RegisterMsgHandler);
    MEMUTIL_VFTABLE_HOOK(0x018053CC,  9, &CGlobalMainProcess::HandleMsg);
    MEMUTIL_VFTABLE_HOOK(0x018053CC, 16, &CGlobalMainProcess::SendMsgToServerBodyDirectly);
    MEMUTIL_VFTABLE_HOOK(0x018053CC, 38, &CGlobalMainProcess::OnENM_SESSION_LOST);
}

int64_t CGlobalMainProcess::RegisterMsgHandler()
{
    DWORD* vtable = *(DWORD**)this;
    tRegisterPacket fRegisterHandler = (tRegisterPacket)vtable[8];

    fRegisterHandler(this, 0x623D, (void*)CustomMsgHandler);

    return reinterpret_thiscall(0x0169AD90, int64_t, this);
}

int32_t CGlobalMainProcess::HandleMsg(CMsg *pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg *pMassiveMsg)
{
    return reinterpret_thiscall(0x0173B810, int32_t, this, pMsg, dwOverlappedJobID, lpParam, pMassiveMsg);
}

void CGlobalMainProcess::SendMsgToServerBodyDirectly(CMsg *pMsg, DWORD dwOverlappedJobID, LPVOID lpParam,
                                                     CMassiveMsg *pMassiveMsg)
{
    reinterpret_thiscall(0x0173CDA0, void, this, pMsg, dwOverlappedJobID, lpParam, pMassiveMsg);
}

int* CGlobalMainProcess::OnENM_SESSION_LOST(CMsg *pMsg, DWORD dwOverlappedJobID, LPVOID lpParam,
                                            CMassiveMsg *pMassiveMsg)
{
    return reinterpret_thiscall(0x01745940, int*, this, pMsg, dwOverlappedJobID, lpParam, pMassiveMsg);
}

/*
 char __stdcall sub_173C4F0(int a1, int a2)
 * */