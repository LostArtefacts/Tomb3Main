#pragma once

#include "global/types.h"

// clang-format off
#define S_ExitSystem    ((void (*)(const char *exit_message))0x004B37C0)
#define SoundEffect     ((int32_t (*)(int32_t sfx_num, struct PHD_3DPOS *pos, int32_t flags))0x00467840)
#define Lara_LookUpDown ((void (*)(void))0x004446E0)
#define Lara_FloorFront ((int16_t (*)(struct ITEM_INFO *item, PHD_ANGLE ang, int32_t dist))0x00444D80)
#define GetHeight       ((int32_t (*)(struct FLOOR_INFO *floor, int32_t x, int32_t y, int32_t z))0x00420E10)
#define GetFloor        ((struct FLOOR_INFO *(*)(int32_t x, int32_t y, int32_t z, int16_t *room_num))0x00420A80)
#define AnimateLara     ((void (*)(struct ITEM_INFO *item))0x0044D2A0)
// clang-format on
