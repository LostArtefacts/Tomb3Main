#pragma once

#include "global/types.h"

// clang-format off
#define Shell_ExitSystem         ((void (*)(const char *exit_message))0x004B37C0)
#define Sound_StopEffect         ((void (*)(int32_t sfx_num))0x00467D00)
#define Sound_PlayEffect         ((int32_t (*)(int32_t sfx_num, struct PHD_3DPOS *pos, int32_t flags))0x00467840)
#define Lara_Animate             ((void (*)(struct ITEM_INFO *item))0x0044D2A0)
#define Lara_WaterCurrent        ((void (*)(struct COLL_INFO *coll))0x0044F310)
#define Gun_Control              ((void (*)(void))0x00449BB0)
#define Item_Animate             ((void (*)(struct ITEM_INFO *item))0x00420590)
#define Kayak_Control            ((int32_t (*)(void))0x0043B730)
#define QuadBike_Control         ((int32_t (*)(void))0x0045EE20)
#define UPV_Control              ((int32_t (*)(void))0x00468C10)
#define BigGun_Control           ((int32_t (*)(struct COLL_INFO *coll))0x00411100)
#define MineCart_Control         ((int32_t (*)(void))0x00453B80)
#define Matrix_TranslateRel_ID   ((void (*)(int32_t x, int32_t y, int32_t z, int32_t x2, int32_t y2, int32_t z2))0x00429500)
#define Matrix_TranslateRel_I    ((void (*)(int32_t x, int32_t y, int32_t z))0x004294B0)
#define Matrix_RotYXZSuperpack_I ((void (*)(int16_t **pprot1, int16_t **pprot2, int32_t skip))0x004295A0)
#define Matrix_RotYXZ_I          ((void (*)(int16_t y, int16_t x, int16_t z))0x00429550)
#define Matrix_InitInterpolate   ((void (*)(int32_t frac, int32_t rate))0x00429350)
#define Matrix_Interpolate       ((void (*)(void))0x004296C0)
#define Matrix_InterpolateArms   ((void (*)(void))0x00429930)
#define Inv_AddItem              ((int32_t (*)(int32_t item_num))0x004378B0)
#define Item_UpdateRoom          ((void (*)(struct ITEM_INFO *item, int32_t height))0x0041E6D0)
#define Room_TestTriggers        ((void (*)(int16_t *data, int32_t heavy))0x00421460)
#define Overlay_DisplayModeInfo  ((void (*)(char *string))0x00434DB0)
#define Text_DrawText            ((void (*)(struct TEXTSTRING *txt))0x0046B340)
#define Text_GetScaleH           ((uint32_t (*)(uint32_t scale_h))0x0046B6F0)
#define Text_GetScaleV           ((uint32_t (*)(uint32_t scale_v))0x0046B720)
// clang-format on

// clang-format off
// TODO: apply naming conventions
#define Lara_BaddieCollision      ((void (*)(struct ITEM_INFO *lara_item, struct COLL_INFO *coll))0x0041E8D0)
#define GetCollisionInfo         ((void (*)(struct COLL_INFO *info, int32_t x, int32_t y, int32_t z, int16_t room_num, int32_t obj_height))0x0041D500)
#define GetStaticObjects         ((int32_t (*)(struct ITEM_INFO *item, PHD_ANGLE ang, int32_t height, int32_t radius, int32_t dist))0x00445020)
#define GetWaterHeight           ((int32_t (*)(int32_t x, int32_t y, int32_t z, int16_t room_num))0x00420C70)
#define TriggerWaterfallMist     ((void (*)(int32_t x, int32_t y, int32_t z, int32_t angle))0x0042D1F0)
#define GetHeight                ((int32_t (*)(struct FLOOR_INFO *floor, int32_t x, int32_t y, int32_t z))0x00420E10)
#define GetCeiling               ((int32_t (*)(struct FLOOR_INFO *floor, int32_t x, int32_t y, int32_t z))0x00421DE0)
#define GetFloor                 ((struct FLOOR_INFO *(*)(int32_t x, int32_t y, int32_t z, int16_t *room_num))0x00420A80)
#define AlterFOV                 ((void (*)(PHD_ANGLE fov))0x00402030)
#define GetFrames                ((int32_t (*)(struct ITEM_INFO *item, int16_t *frm[], int32_t *rate))0x00429DB0)
#define ShiftItem                ((void (*)(struct ITEM_INFO *item, struct COLL_INFO *coll))0x0041E690)
#define GetBoundsAccurate        ((int16_t *(*)(struct ITEM_INFO *item))0x00429E50)
#define phd_sqrt                 ((int32_t (__fastcall *)(int32_t n))0x004B4C93)
#define phd_cos                  ((int32_t (__fastcall *)(int32_t angle))0x004B4C58)
#define phd_sin                  ((int32_t (__fastcall *)(int32_t angle))0x004B4C5E)
// clang-format on
