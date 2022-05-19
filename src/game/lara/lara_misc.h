#pragma once

// Lara collision helpers.

#include "global/types.h"

#include <stdbool.h>
#include <stdint.h>

PHD_ANGLE Lara_SnapAngle(PHD_ANGLE angle, PHD_ANGLE snap);
enum DIRECTION Lara_AngleToDirection(PHD_ANGLE angle);

void Lara_GetCollisionInfo(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_SlideSlope(struct ITEM_INFO *item, struct COLL_INFO *coll);
bool Lara_HitCeiling(struct ITEM_INFO *item, struct COLL_INFO *coll);
bool Lara_DeflectEdge(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_DeflectEdgeJump(struct ITEM_INFO *item, struct COLL_INFO *coll);
bool Lara_DeflectEdgeDuck(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_SlideEdgeJump(struct ITEM_INFO *item, struct COLL_INFO *coll);
bool Lara_TestVault(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_TestHang(struct ITEM_INFO *item, struct COLL_INFO *coll);
bool Lara_TestHangOnClimbWall(struct ITEM_INFO *item, struct COLL_INFO *coll);
bool Lara_TestHangJump(struct ITEM_INFO *item, struct COLL_INFO *coll);
bool Lara_TestHangSwingIn(struct ITEM_INFO *item, PHD_ANGLE angle);
bool Lara_TestClimbStance(struct ITEM_INFO *item, struct COLL_INFO *coll);
bool Lara_TestSlide(struct ITEM_INFO *item, struct COLL_INFO *coll);
bool Lara_LandedBad(struct ITEM_INFO *item, struct COLL_INFO *coll);
int32_t Lara_TestWall(
    struct ITEM_INFO *item, int32_t front, int32_t right, int32_t down);
int16_t Lara_FloorFront(struct ITEM_INFO *item, PHD_ANGLE ang, int32_t dist);
void Lara_MonkeySwingFall(struct ITEM_INFO *item);
int16_t Lara_CeilingFront(struct ITEM_INFO *item, PHD_ANGLE ang, int32_t dist);
bool Lara_Fallen(struct ITEM_INFO *item, struct COLL_INFO *coll);
int32_t Lara_TestEdgeCatch(
    struct ITEM_INFO *item, struct COLL_INFO *coll, int32_t *edge);
int32_t Lara_TestClimb(
    int32_t x, int32_t y, int32_t z, int32_t x_front, int32_t z_front,
    int32_t item_height, int16_t item_room, int32_t *shift);
int32_t Lara_TestClimbUpPos(
    struct ITEM_INFO *item, int32_t front, int32_t right, int32_t *shift,
    int32_t *ledge);
int32_t Lara_TestClimbPos(
    struct ITEM_INFO *item, int32_t front, int32_t right, int32_t origin,
    int32_t height, int32_t *shift);
