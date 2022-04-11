#pragma once

#include "global/types.h"

PHD_ANGLE Lara_SnapAngle(PHD_ANGLE angle, PHD_ANGLE snap);
enum DIRECTION Lara_AngleToDirection(PHD_ANGLE angle);

bool Lara_TestSlide(struct ITEM_INFO *item, struct COLL_INFO *coll);
bool Lara_TestClimbStance(struct ITEM_INFO *item, struct COLL_INFO *coll);
bool Lara_TestVault(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_SlideSlope(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_GetCollisionInfo(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_DeflectEdgeJump(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_SlideEdgeJump(struct ITEM_INFO *item, struct COLL_INFO *coll);
bool Lara_TestHangOnClimbWall(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_TestHang(struct ITEM_INFO *item, struct COLL_INFO *coll);
bool Lara_TestHangJump(struct ITEM_INFO *item, struct COLL_INFO *coll);
bool Lara_TestHangSwingIn(struct ITEM_INFO *item, PHD_ANGLE angle);
bool Lara_DeflectEdgeDuck(struct ITEM_INFO *item, struct COLL_INFO *coll);
int32_t Lara_TestWall(
    struct ITEM_INFO *item, int32_t front, int32_t right, int32_t down);
void Lara_MonkeySwingFall(struct ITEM_INFO *item);
bool Lara_LandedBad(struct ITEM_INFO *item, struct COLL_INFO *coll);
bool Lara_HitCeiling(struct ITEM_INFO *item, struct COLL_INFO *coll);
int16_t Lara_FloorFront(struct ITEM_INFO *item, PHD_ANGLE ang, int32_t dist);
int16_t Lara_CeilingFront(struct ITEM_INFO *item, PHD_ANGLE ang, int32_t dist);
bool Lara_Fallen(struct ITEM_INFO *item, struct COLL_INFO *coll);

void Lara_GetHandAbsPosition(
    struct PHD_VECTOR *vec, enum LARA_BODY_PART body_part);
void Lara_GetHandAbsPosition_I(
    struct ITEM_INFO *item, struct PHD_VECTOR *vec, int16_t *frame1,
    int16_t *frame2, int32_t frac, int32_t rate, enum LARA_BODY_PART body_part);

void Lara_ResetLook(void);
void Lara_LookUpDown(void);
void Lara_LookLeftRight(void);
void Lara_AboveWater(struct ITEM_INFO *item, struct COLL_INFO *coll);

void Lara_State_Duck(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_AllFours(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_AllFoursTurnLeft(
    struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_AllFoursTurnRight(
    struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_Crawl(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_CrawlB(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_Dash(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_DashDive(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_MonkeyHang(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_MonkeySwing(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_MonkeyLeft(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_MonkeyRight(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_HangTurnLeft(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_HangTurnRight(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_Monkey180(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_Stop(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_JumpUp(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_ForwardJump(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_Walk(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_Run(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_FastBack(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_TurnRight(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_TurnLeft(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_Death(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_FastFall(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_Hang(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_Reach(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_Splat(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_Compress(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_Back(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_FastTurn(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_StepRight(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_StepLeft(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_Slide(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_BackJump(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_RightJump(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_LeftJump(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_FallBack(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_HangLeft(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_HangRight(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_SlideBack(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_PushBlock(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_PushPullReady(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_Pickup(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_PickupFlare(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_SwitchOn(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_UseKey(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_Special(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_SwanDive(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_FastDive(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_Null(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_WaterOut(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_Wade(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_State_DeathSlide(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_StateExtra_Breath(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_StateExtra_SharkKill(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_StateExtra_AirLock(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_StateExtra_GongBong(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_StateExtra_TRexDeath(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_StateExtra_StartAnim(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_StateExtra_TrainKill(struct ITEM_INFO *item, struct COLL_INFO *col);

void Lara_Col_Duck(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_AllFours(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_AllFoursTurnLR(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Crawl(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_CrawlB(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Crawl2Hang(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Dash(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_DashDive(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_MonkeySwingHang(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_MonkeySwing(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_MonkeyLeft(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_MonkeyRight(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_HangTurnLR(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Monkey180(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Stop(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_JumpUp(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Walk(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Run(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_JumpForward(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_FastBack(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_TurnRight(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_TurnLeft(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Death(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_FastFall(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Hang(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Reach(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Splat(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Land(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Compress(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Back(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_StepRight(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_StepLeft(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Slide(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_JumpBack(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_JumpRight(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_JumpLeft(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_FallBack(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_HangLeft(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_HangRight(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_SlideBack(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Null(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Roll(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Roll2(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_SwanDive(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_FastDive(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Wade(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_Col_Default(struct ITEM_INFO *item, struct COLL_INFO *coll);
