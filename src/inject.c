#include "inject.h"

#include "game/lara.h"
#include "inject_util.h"

void Inject_All(void)
{
    INJECT(0x0043D780, Lara_TestSlide, 1);
    INJECT(0x0043D8C0, Lara_TestClimbStance, 1);
    INJECT(0x0043D980, Lara_TestVault, 1);
    INJECT(0x0043DCF0, Lara_SlideSlope, 1);
    INJECT(0x0043DE00, Lara_GetCollisionInfo, 1);
    INJECT(0x0043DE40, Lara_DeflectEdgeJump, 1);
    INJECT(0x0043DFC0, Lara_SlideEdgeJump, 1);
    INJECT(0x0043E0B0, Lara_TestHangOnClimbWall, 1);
    INJECT(0x0043E1C0, Lara_TestHang, 1);
    INJECT(0x0043E4E0, Lara_TestHangJump, 1);
    INJECT(0x0043E730, Lara_TestHangSwingIn, 1);
    INJECT(0x0043F0D0, Lara_DeflectEdgeDuck, 1);
    INJECT(0x0043F870, Lara_TestWall, 1);

    INJECT(0x0043E800, Lara_AboveWater, 1);

    INJECT(0x0043EA20, Lara_State_Duck, 1);
    INJECT(0x0043EBA0, Lara_State_AllFours, 1);
    INJECT(0x0043F150, Lara_State_AllFoursTurnLeft, 1);
    INJECT(0x0043F1F0, Lara_State_AllFoursTurnRight, 1);
    INJECT(0x0043EF10, Lara_State_Crawl, 1);
    INJECT(0x0043F260, Lara_State_CrawlB, 1);
    INJECT(0x0043F600, Lara_State_Dash, 1);
    INJECT(0x0043FA40, Lara_State_DashDive, 1);
    INJECT(0x0043FB90, Lara_State_MonkeyHang, 1);
    INJECT(0x004400A0, Lara_State_MonkeySwing, 1);
    INJECT(0x00440220, Lara_State_MonkeyLeft, 1);
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
    INJECT(0x00441840, Lara_State_PushPullReady, 1);
    INJECT(0x00441870, Lara_State_Pickup, 1);
    INJECT(0x004418B0, Lara_State_PickupFlare, 1);
    INJECT(0x00441910, Lara_State_SwitchOn, 1);
    INJECT(0x00441950, Lara_State_UseKey, 1);
    INJECT(0x00441990, Lara_State_Special, 1);
    INJECT(0x004419B0, Lara_State_SwanDive, 1);
    INJECT(0x004419F0, Lara_State_FastDive, 1);
    INJECT(0x00441A50, Lara_State_Null, 1);
    INJECT(0x00441A60, Lara_State_WaterOut, 1);
    INJECT(0x00441A80, Lara_State_Wade, 1);
    INJECT(0x00441C00, Lara_State_DeathSlide, 1);
    INJECT(0x00441CA0, Lara_StateExtra_Breath, 1);
    INJECT(0x00441CF0, Lara_StateExtra_SharkKill, 1);
    INJECT(0x00441D90, Lara_StateExtra_AirLock, 1);
    INJECT(0x00441DB0, Lara_StateExtra_GongBong, 1);
    INJECT(0x00441DD0, Lara_StateExtra_TRexDeath, 1);
    INJECT(0x00441E30, Lara_StateExtra_StartAnim, 1);
    INJECT(0x00441E80, Lara_StateExtra_TrainKill, 1);
}
