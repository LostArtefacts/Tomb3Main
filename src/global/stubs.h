#pragma once

#include "global/types.h"

// clang-format off
#define Shell_ExitSystem      ((void (*)(const char *exit_message))0x004B37C0)
#define Sound_PlayEffect      ((int32_t (*)(int32_t sfx_num, struct PHD_3DPOS *pos, int32_t flags))0x00467840)
#define Lara_LookUpDown       ((void (*)(void))0x004446E0)
#define Lara_FloorFront       ((int16_t (*)(struct ITEM_INFO *item, PHD_ANGLE ang, int32_t dist))0x00444D80)
#define Lara_Animate          ((void (*)(struct ITEM_INFO *item))0x0044D2A0)
#define Lara_GetCollisionInfo ((void (*)(struct ITEM_INFO *item, struct COLL_INFO *coll))0x0043DE00)
#define Lara_TestClimbPos     ((int32_t (*)(struct ITEM_INFO *item, int32_t front, int32_t right, int32_t origin, int32_t height, int32_t *shift))0x00449090)
#define Random_GetControl     ((int32_t (*)(void))0x004841F0)
// clang-format on

// clang-format off
// TODO: apply naming conventions
#define GetWaterHeight        ((int32_t (*)(int32_t x, int32_t y, int32_t z, int16_t room_num))0x00420C70)
#define TriggerWaterfallMist  ((void (*)(int32_t x, int32_t y, int32_t z, int32_t angle))0x0042D1F0)
#define GetHeight             ((int32_t (*)(struct FLOOR_INFO *floor, int32_t x, int32_t y, int32_t z))0x00420E10)
#define GetFloor              ((struct FLOOR_INFO *(*)(int32_t x, int32_t y, int32_t z, int16_t *room_num))0x00420A80)
#define AlterFOV              ((void (*)(PHD_ANGLE fov))0x00402030)
#define TestTriggers          ((void (*)(int16_t *data, int32_t heavy))0x00421460)
#define ShiftItem             ((void (*)(struct ITEM_INFO *item, struct COLL_INFO *coll))0x0041E690)
// clang-format on
