#include "game/matrix.h"

#include "global/const.h"
#include "global/vars.h"

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
