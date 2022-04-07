#pragma once

#include "global/types.h"

// clang-format off
#define Shell_ExitSystem      ((void (*)(const char *exit_message))0x004B37C0)
#define Sound_StopEffect      ((void (*)(int32_t sfx_num))0x00467D00)
#define Sound_PlayEffect      ((int32_t (*)(int32_t sfx_num, struct PHD_3DPOS *pos, int32_t flags))0x00467840)
#define Lara_LookUpDown       ((void (*)(void))0x004446E0)
#define Lara_LookLeftRight    ((void (*)(void))0x00444770)
#define Lara_ResetLook        ((void (*)(void))0x00444800)
#define Lara_FloorFront       ((int16_t (*)(struct ITEM_INFO *item, PHD_ANGLE ang, int32_t dist))0x00444D80)
#define Lara_CeilingFront     ((int16_t (*)(struct ITEM_INFO *item, PHD_ANGLE ang, int32_t dist))0x00444E00)
#define Lara_Animate          ((void (*)(struct ITEM_INFO *item))0x0044D2A0)
#define Lara_DeflectEdge      ((int32_t (*)(struct ITEM_INFO *item, struct COLL_INFO *coll))0x00444F90)
#define Lara_TestClimbPos     ((int32_t (*)(struct ITEM_INFO *item, int32_t front, int32_t right, int32_t origin, int32_t height, int32_t *shift))0x00449090)
#define Lara_Fallen           ((int32_t (*)(struct ITEM_INFO *item, struct COLL_INFO *coll))0x00444E80)
#define Lara_HitCeiling       ((int32_t (*)(struct ITEM_INFO *item, struct COLL_INFO *coll))0x00444D10)
#define Lara_LandedBad        ((int32_t (*)(struct ITEM_INFO *item, struct COLL_INFO *coll))0x00444C20)
#define Lara_TestEdgeCatch    ((int32_t (*)(struct ITEM_INFO *item, struct COLL_INFO *coll, int32_t *edge))0x00444EE0)
#define Lara_Col_Jumper       ((void (*)(struct ITEM_INFO *item, struct COLL_INFO *coll))0x004432E0)
#define Lara_Gun              ((void (*)(void))0x00449BB0)
#define Random_GetControl     ((int32_t (*)(void))0x004841F0)
#define GetCeiling            ((int32_t (*)(struct FLOOR_INFO *floor, int32_t x, int32_t y, int32_t z))0x00421DE0)
#define Kayak_Control         ((int32_t (*)(void))0x0043B730)
#define QuadBike_Control      ((int32_t (*)(void))0x0045EE20)
#define UPV_Control           ((int32_t (*)(void))0x00468C10)
#define BigGun_Control        ((int32_t (*)(struct COLL_INFO *coll))0x00411100)
#define MineCart_Control      ((int32_t (*)(void))0x00453B80)
// clang-format on

// clang-format off
// TODO: apply naming conventions
#define UpdateLaraRoom        ((void (*)(struct ITEM_INFO *item, int32_t height))0x0041E6D0)
#define LaraBaddieCollision   ((void (*)(struct ITEM_INFO *lara_item, struct COLL_INFO *coll))0x0041E8D0)
#define GetCollisionInfo      ((void (*)(struct COLL_INFO *info, int32_t x, int32_t y, int32_t z, int16_t room_num, int32_t obj_height))0x0041D500)
#define GetStaticObjects      ((int32_t (*)(struct ITEM_INFO *item, PHD_ANGLE ang, int32_t height, int32_t radius, int32_t dist))0x00445020)
#define GetWaterHeight        ((int32_t (*)(int32_t x, int32_t y, int32_t z, int16_t room_num))0x00420C70)
#define TriggerWaterfallMist  ((void (*)(int32_t x, int32_t y, int32_t z, int32_t angle))0x0042D1F0)
#define GetHeight             ((int32_t (*)(struct FLOOR_INFO *floor, int32_t x, int32_t y, int32_t z))0x00420E10)
#define GetFloor              ((struct FLOOR_INFO *(*)(int32_t x, int32_t y, int32_t z, int16_t *room_num))0x00420A80)
#define AlterFOV              ((void (*)(PHD_ANGLE fov))0x00402030)
#define TestTriggers          ((void (*)(int16_t *data, int32_t heavy))0x00421460)
#define ShiftItem             ((void (*)(struct ITEM_INFO *item, struct COLL_INFO *coll))0x0041E690)
#define GetBoundsAccurate     ((int16_t *(*)(struct ITEM_INFO *item))0x00429E50)
#define phd_sqrt              ((int32_t (__fastcall *)(int32_t n))0x004B4C93)
#define phd_cos               ((int32_t (__fastcall *)(int32_t angle))0x004B4C58)
#define phd_sin               ((int32_t (__fastcall *)(int32_t angle))0x004B4C5E)
// clang-format on
