#include "FarmMainProcess.h"
#include "utils/MemoryUtility.h"
#include "BSLib/HydraFramework.h"
#include "BSLib/NetEngine/NetEngine.h"

typedef void (__thiscall* tRegisterPacket)(void* pThis, unsigned short opcode, void* handlerProc);

int __cdecl FarmManagerNewMsgHandler(CMsg *pMsg)
{
    if (g_pHydraMainProcess) {
        g_pHydraMainProcess->HandleMsg(pMsg);
    }
    return 1;
}

void CFarmManagerMainProcess::SetupHook()
{
    MEMUTIL_VFTABLE_HOOK(0x01529AFC, 7, &CFarmManagerMainProcess::RegisterMsgHandler);
    MEMUTIL_VFTABLE_HOOK(0x01529AFC, 9, &CFarmManagerMainProcess::HandleMsg);
}

int32_t CFarmManagerMainProcess::RegisterMsgHandler()
{
    DWORD* vtable = *(DWORD**)this;
    tRegisterPacket RegisterPacket = (tRegisterPacket)vtable[8];

    RegisterPacket(this, 0x623D, (void*)FarmManagerNewMsgHandler);

    return reinterpret_thiscall(0x014459C0, int32_t, this);
}

uint32_t CFarmManagerMainProcess::HandleMsg(CMsg *pMsg, DWORD dwOverlappedID, LPVOID lpParam, CMassiveMsg *pMassiveMsg)
{
    if (pMsg) g_pHydraMainProcess->HandleMsg(pMsg);
    return reinterpret_thiscall(0x014501A0, uint32_t, this, pMsg, dwOverlappedID, lpParam, pMassiveMsg);
}

uint8_t CFarmManagerMainProcess::GetServerBodyID(const char* moduleName)
{
    int pModule = reinterpret_cdecl(0x01472D20, int, moduleName);
    if (!pModule) return NULL;
    return *(unsigned char*)pModule;
}