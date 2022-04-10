#include "game/matrix.h"

#include "global/const.h"
#include "global/stubs.h"
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

void Matrix_TranslateAbs(int32_t x, int32_t y, int32_t z)
{
    struct MATRIX *m = g_MatrixPtr;
    x -= g_W2VMatrix._03;
    z -= g_W2VMatrix._23;
    y -= g_W2VMatrix._13;
    m->_03 = x * m->_00 + y * m->_01 + z * m->_02;
    m->_13 = x * m->_10 + y * m->_11 + z * m->_12;
    m->_23 = x * m->_20 + y * m->_21 + z * m->_22;
}

void Matrix_RotX(PHD_ANGLE rx)
{
    if (!rx) {
        return;
    }

    struct MATRIX *m = g_MatrixPtr;
    int32_t sx = phd_sin(rx);
    int32_t cx = phd_cos(rx);
    int32_t r0, r1;

    r0 = (cx * m->_01 + sx * m->_02);
    r1 = (cx * m->_02 - sx * m->_01);
    m->_01 = r0 >> W2V_SHIFT;
    m->_02 = r1 >> W2V_SHIFT;

    r0 = (cx * m->_11 + sx * m->_12);
    r1 = (cx * m->_12 - sx * m->_11);
    m->_11 = r0 >> W2V_SHIFT;
    m->_12 = r1 >> W2V_SHIFT;

    r0 = (cx * m->_21 + sx * m->_22);
    r1 = (cx * m->_22 - sx * m->_21);
    m->_21 = r0 >> W2V_SHIFT;
    m->_22 = r1 >> W2V_SHIFT;
}
