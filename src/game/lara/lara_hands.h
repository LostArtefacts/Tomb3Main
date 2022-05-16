#pragma once

#include "global/types.h"

#include <stdint.h>

void Lara_GetHandAbsPosition(
    struct PHD_VECTOR *vec, enum LARA_BODY_PART body_part);

void Lara_GetHandAbsPosition_I(
    struct ITEM_INFO *item, struct PHD_VECTOR *vec, int16_t *frame1,
    int16_t *frame2, int32_t frac, int32_t rate, enum LARA_BODY_PART body_part);
