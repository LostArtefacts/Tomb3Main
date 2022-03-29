#pragma once

#include "global/types.h"

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
