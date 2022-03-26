#pragma once

#include "global/types.h"

// clang-format off
#define S_ExitSystem ((void (*)(const char *exit_message))0x004B37C0)
#define SoundEffect  ((int32_t (*)(int32_t sfx_num, struct PHD_3DPOS *pos, int32_t flags))0x00467840)
// clang-format on
