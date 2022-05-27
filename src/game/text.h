#pragma once

#include "global/types.h"

void Text_Init(void);
struct TEXTSTRING *Text_Create(
    int32_t x, int32_t y, int32_t colour, const char *string);
void Text_Change(struct TEXTSTRING *txt, const char *string);
void Text_Flash(struct TEXTSTRING *txt, bool enable, int16_t rate);
void Text_AddBackground(
    struct TEXTSTRING *txt, int16_t w, int16_t h, int16_t x, int16_t y,
    int16_t z, int16_t colour, uint16_t *gourptr, uint16_t flags);
