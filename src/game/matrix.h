#pragma once

#include <stdbool.h>
#include <stdint.h>

void Matrix_Push(void);
void Matrix_PushUnit(void);
void Matrix_Pop(void);
bool Matrix_TranslateRel(int32_t x, int32_t y, int32_t z);
