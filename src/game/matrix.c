#include "game/matrix.h"

#include "global/const.h"
#include "global/vars.h"
#include "util.h"

void Matrix_Push(void)
{
    g_MatrixPtr++;
    g_MatrixPtr[0] = g_MatrixPtr[-1];
}

void Matrix_PushUnit(void)
{
    g_MatrixPtr++;
    g_MatrixPtr->_00 = 1 << W2V_SHIFT;
    g_MatrixPtr->_01 = 0;
    g_MatrixPtr->_02 = 0;

    g_MatrixPtr->_10 = 0;
    g_MatrixPtr->_11 = 1 << W2V_SHIFT;
    g_MatrixPtr->_12 = 0;

    g_MatrixPtr->_20 = 0;
    g_MatrixPtr->_21 = 0;
    g_MatrixPtr->_22 = 1 << W2V_SHIFT;
}

void Matrix_Pop(void)
{
    g_MatrixPtr--;
}

bool Matrix_TranslateRel(int32_t x, int32_t y, int32_t z)
{
    struct MATRIX *m = g_MatrixPtr;
    m->_03 += x * m->_00 + y * m->_01 + z * m->_02;
    m->_13 += x * m->_10 + y * m->_11 + z * m->_12;
    m->_23 += x * m->_20 + y * m->_21 + z * m->_22;
    return ABS(m->_03) <= g_ZFar && ABS(m->_13) <= g_ZFar
        && ABS(m->_23) <= g_ZFar;
}
