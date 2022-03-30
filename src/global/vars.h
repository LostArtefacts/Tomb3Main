#pragma once

#include "global/types.h"
#include "inject_util.h"

#define g_Input VAR(0x0069FDF0, uint32_t)
#define g_Lara VAR(0x006D61A0, struct LARA_INFO)
#define g_Anims VAR(0x006E2074, struct ANIM_INFO *)
#define g_DashTimer VAR(0x006D62A0, int16_t)
#define g_Camera VAR(0x006E3040, struct CAMERA_INFO)
#define g_Rooms VAR(0x006E2890, struct ROOM_INFO *)
#define g_TriggerIndex VAR(0x006E29A8, int16_t *)
#define g_Wibble VAR(0x006261A8, int32_t)
