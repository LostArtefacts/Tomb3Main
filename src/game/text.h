#pragma once

#include "global/types.h"

void Text_Init(void);
struct TEXTSTRING *Text_Create(
    int32_t x, int32_t y, int32_t colour, const char *string);
