#include "GObjPC.h"

DWORD OnAddItemContinue = 0x005DBB20;

__declspec(naked) void OnAddItem_EXT()
{
    // This is the original assembly
    // 0x005DBB1B mov edx,dword ptr ss:[esp+24] || we hooked here
    // 0x005DBB1F push edx                      || btStartSlot
    // 0x005DBB20 mov ecx,esi                   || we return here
    // 0x005DBB22 call 0x0057F040               || CGStorage::GetFirstEmptySlot(btStartSlot)
    __asm
    {
        movzx edx, byte ptr ss:[ebp+0x18]
        cmp edx, 13
        jl use_game_default
        cmp edx, 109
        jg use_game_default
        push edx
        jmp OnAddItemContinue
    use_game_default:
        mov edx, dword ptr ss:[esp+0x24]
        push edx
        jmp OnAddItemContinue
    }
}

void CGObjPC::SetupHook()
{
    MEMUTIL_SETUP_HOOK(LongJump, 0x005DBB1B, OnAddItem_EXT);
}
