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
    INJECT(0x00441450, Lara_State_Back, 1);
    INJECT(0x004414E0, Lara_State_FastTurn, 1);
    INJECT(0x00441530, Lara_State_StepRight, 1);
    INJECT(0x004415B0, Lara_State_StepLeft, 1);
    INJECT(0x00441630, Lara_State_Slide, 1);
    INJECT(0x00441660, Lara_State_BackJump, 1);
    INJECT(0x004416B0, Lara_State_RightJump, 1);
    INJECT(0x004416F0, Lara_State_LeftJump, 1);
    INJECT(0x00441730, Lara_State_FallBack, 1);
    INJECT(0x00441760, Lara_State_HangLeft, 1);
    INJECT(0x004417A0, Lara_State_HangRight, 1);
    INJECT(0x004417E0, Lara_State_SlideBack, 1);
    INJECT(0x00441800, Lara_State_PushBlock, 1);
}
