#include "inject.h"

#include "game/lara.h"
#include "inject_util.h"

void Inject_All(void)
{
    INJECT(0x00440DB0, Lara_State_ForwardJump, 1);
    INJECT(0x00440E90, Lara_State_Walk, 1);
    INJECT(0x00440F20, Lara_State_Run, 1);
    INJECT(0x004410A0, Lara_State_FastBack, 1);
    INJECT(0x00441100, Lara_State_TurnRight, 1);
    INJECT(0x004411A0, Lara_State_TurnLeft, 1);
    INJECT(0x00441240, Lara_State_Death, 1);
    INJECT(0x00441260, Lara_State_FastFall, 1);
    INJECT(0x004412A0, Lara_State_Hang, 1);
    INJECT(0x00441310, Lara_State_Reach, 1);
    INJECT(0x00441330, Lara_State_Splat, 1);
    INJECT(0x00441340, Lara_State_Compress, 1);
}
