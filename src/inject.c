#include "inject.h"

#include "game/lara/lara_col.h"
#include "game/lara/lara_control.h"
#include "game/lara/lara_hands.h"
#include "game/lara/lara_look.h"
#include "game/lara/lara_misc.h"
#include "game/lara/lara_state.h"
#include "game/matrix.h"
#include "game/random.h"
#include "game/text.h"
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
    INJECT(0x0043FC10, Lara_MonkeySwingFall, 1);
    INJECT(0x00444C20, Lara_LandedBad, 1);
    INJECT(0x00444D10, Lara_HitCeiling, 1);
    INJECT(0x00444D80, Lara_FloorFront, 1);
    INJECT(0x00444E00, Lara_CeilingFront, 1);
    INJECT(0x00444E80, Lara_Fallen, 1);
    INJECT(0x00444EE0, Lara_TestEdgeCatch, 1);
    INJECT(0x00444F90, Lara_DeflectEdge, 1);
    INJECT(0x00448BE0, Lara_TestClimb, 1);
    INJECT(0x00448E60, Lara_TestClimbUpPos, 1);
    INJECT(0x00449090, Lara_TestClimbPos, 1);

    INJECT(0x00443360, Lara_GetHandAbsPosition, 1);
    INJECT(0x00443CA0, Lara_GetHandAbsPosition_I, 1);

    INJECT(0x00444800, Lara_ResetLook, 1);
    INJECT(0x004446E0, Lara_LookUpDown, 1);
    INJECT(0x00444770, Lara_LookLeftRight, 1);

    INJECT(0x0043E800, Lara_HandleAboveWater, 1);
    INJECT(0x0044E950, Lara_HandleUnderwater, 1);
    INJECT(0x0044E050, Lara_HandleSurface, 1);
    INJECT(0x0044C630, Lara_CheatGetStuff, 1);

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
    INJECT(0x004402F0, Lara_State_MonkeyRight, 1);
    INJECT(0x004403C0, Lara_State_HangTurnLeft, 1);
    INJECT(0x004404A0, Lara_State_HangTurnRight, 1);
    INJECT(0x004404E0, Lara_State_Monkey180, 1);
    INJECT(0x00440DB0, Lara_State_ForwardJump, 1);
    INJECT(0x00440520, Lara_State_Stop, 1);
    INJECT(0x00440A20, Lara_State_JumpUp, 1);
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
    INJECT(0x00449140, Lara_State_ClimbLeft, 1);
    INJECT(0x00449180, Lara_State_ClimbRight, 1);
    INJECT(0x004491C0, Lara_State_ClimbStance, 1);
    INJECT(0x00449240, Lara_State_Climbing, 1);
    INJECT(0x00449260, Lara_State_ClimbEnd, 1);
    INJECT(0x00449290, Lara_State_ClimbDown, 1);
    INJECT(0x00441CA0, Lara_StateExtra_Breath, 1);
    INJECT(0x00441CF0, Lara_StateExtra_SharkKill, 1);
    INJECT(0x00441D90, Lara_StateExtra_AirLock, 1);
    INJECT(0x00441DB0, Lara_StateExtra_GongBong, 1);
    INJECT(0x00441DD0, Lara_StateExtra_TRexDeath, 1);
    INJECT(0x00441E30, Lara_StateExtra_StartAnim, 1);
    INJECT(0x00441E80, Lara_StateExtra_TrainKill, 1);

    INJECT(0x0043EAA0, Lara_Col_Duck, 1);
    INJECT(0x0043EC20, Lara_Col_AllFours, 1);
    INJECT(0x0043F1C0, Lara_Col_AllFoursTurnLR, 1);
    INJECT(0x0043EFE0, Lara_Col_Crawl, 1);
    INJECT(0x0043F330, Lara_Col_CrawlB, 1);
    INJECT(0x0043F430, Lara_Col_Crawl2Hang, 1);
    INJECT(0x0043F720, Lara_Col_Dash, 1);
    INJECT(0x0043FA70, Lara_Col_DashDive, 1);
    INJECT(0x0043FC70, Lara_Col_MonkeySwingHang, 1);
    INJECT(0x00440140, Lara_Col_MonkeySwing, 1);
    INJECT(0x00440280, Lara_Col_MonkeyLeft, 1);
    INJECT(0x00440350, Lara_Col_MonkeyRight, 1);
    INJECT(0x00440400, Lara_Col_HangTurnLR, 1);
    INJECT(0x00440500, Lara_Col_Monkey180, 1);
    INJECT(0x00440960, Lara_Col_Stop, 1);
    INJECT(0x00440A40, Lara_Col_JumpUp, 1);
    INJECT(0x00441F90, Lara_Col_Walk, 1);
    INJECT(0x00442140, Lara_Col_Run, 1);
    INJECT(0x004422D0, Lara_Col_JumpForward, 1);
    INJECT(0x004423B0, Lara_Col_FastBack, 1);
    INJECT(0x00442490, Lara_Col_TurnRight, 1);
    INJECT(0x00442580, Lara_Col_TurnLeft, 1);
    INJECT(0x004425A0, Lara_Col_Death, 1);
    INJECT(0x00442610, Lara_Col_FastFall, 1);
    INJECT(0x004426B0, Lara_Col_Hang, 1);
    INJECT(0x00442830, Lara_Col_Reach, 1);
    INJECT(0x004428E0, Lara_Col_Splat, 1);
    INJECT(0x00442950, Lara_Col_Land, 1);
    INJECT(0x00442970, Lara_Col_Compress, 1);
    INJECT(0x00442A10, Lara_Col_Back, 1);
    INJECT(0x00442B50, Lara_Col_StepRight, 1);
    INJECT(0x00442C30, Lara_Col_StepLeft, 1);
    INJECT(0x00442C50, Lara_Col_Slide, 1);
    INJECT(0x00442C70, Lara_Col_JumpBack, 1);
    INJECT(0x00442CA0, Lara_Col_JumpRight, 1);
    INJECT(0x00442CD0, Lara_Col_JumpLeft, 1);
    INJECT(0x00442D00, Lara_Col_FallBack, 1);
    INJECT(0x00442D90, Lara_Col_HangLeft, 1);
    INJECT(0x00442DD0, Lara_Col_HangRight, 1);
    INJECT(0x00442E10, Lara_Col_SlideBack, 1);
    INJECT(0x00442E40, Lara_Col_Null, 1);
    INJECT(0x00442E60, Lara_Col_Roll, 1);
    INJECT(0x00442F00, Lara_Col_Roll2, 1);
    INJECT(0x00442FD0, Lara_Col_SwanDive, 1);
    INJECT(0x00443040, Lara_Col_FastDive, 1);
    INJECT(0x004430C0, Lara_Col_Wade, 1);
    INJECT(0x004492B0, Lara_Col_ClimbLeft, 1);
    INJECT(0x004494D0, Lara_Col_ClimbRight, 1);
    INJECT(0x00449530, Lara_Col_ClimbStance, 1);
    INJECT(0x00449740, Lara_Col_Climbing, 1);
    INJECT(0x00449890, Lara_Col_ClimbDown, 1);
    INJECT(0x00443290, Lara_Col_Default, 1);

    INJECT(0x004B4280, Matrix_Push, 1);
    INJECT(0x004B429E, Matrix_PushUnit, 1);
    INJECT(0x004019C0, Matrix_TranslateRel, 1);
    INJECT(0x00401A70, Matrix_TranslateAbs, 1);
    INJECT(0x004013E0, Matrix_RotX, 1);
    INJECT(0x00401490, Matrix_RotY, 1);
    INJECT(0x00401540, Matrix_RotZ, 1);
    INJECT(0x004015F0, Matrix_RotYXZ, 1);
    INJECT(0x004017D0, Matrix_RotYXZPack, 1);
    INJECT(0x004295E0, Matrix_RotYXZSuperpack, 1);

    INJECT(0x00484210, Random_SeedControl, 1);
    INJECT(0x00484240, Random_SeedDraw, 1);
    INJECT(0x004841F0, Random_GetControl, 1);
    INJECT(0x00484220, Random_GetDraw, 1);

    INJECT(0x0046AC70, Text_Init, 1);
    INJECT(0x0046ACA0, Text_Create, 1);
    INJECT(0x0046AD90, Text_Change, 1);
    INJECT(0x0046ADD0, Text_Flash, 1);
    INJECT(0x0046AE00, Text_AddBackground, 1);
    INJECT(0x0046AE90, Text_RemoveBackground, 1);
    INJECT(0x0046AEA0, Text_AddOutline, 1);
    INJECT(0x0046AED0, Text_RemoveOutline, 1);
    INJECT(0x0046AEE0, Text_CentreH, 1);
    INJECT(0x0046AF00, Text_CentreV, 1);
    INJECT(0x0046AF20, Text_AlignRight, 1);
    INJECT(0x0046AF40, Text_AlignBottom, 1);
    INJECT(0x0046AF60, Text_GetWidth, 1);
    INJECT(0x0046B090, Text_RemovePrint, 1);
    INJECT(0x0046B0F0, Text_Draw, 1);
    INJECT(0x0046B120, Text_DrawBorder, 1);
    INJECT(0x0046B340, Text_DrawText, 1);
}
