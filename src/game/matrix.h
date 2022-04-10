#pragma once

#include "global/types.h"

void Matrix_Push(void);
void Matrix_PushUnit(void);
void Matrix_Pop(void);
bool Matrix_TranslateRel(int32_t x, int32_t y, int32_t z);
void Matrix_TranslateAbs(int32_t x, int32_t y, int32_t z);
void Matrix_RotX(PHD_ANGLE rx);
void Matrix_RotY(PHD_ANGLE ry);
void Matrix_RotZ(PHD_ANGLE rz);
void Matrix_RotYXZ(PHD_ANGLE ry, PHD_ANGLE rx, PHD_ANGLE rz);
void Matrix_RotYXZPack(int32_t rots);
void Matrix_RotYXZSuperpack(int16_t **pprot, int32_t skip);
