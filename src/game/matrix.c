#include "game/matrix.h"

#include "global/vars.h"

void Matrix_Push(void)
{
    g_MatrixPtr[1] = g_MatrixPtr[0];
    g_MatrixPtr++;
}

void Matrix_Pop(void)
{
    g_MatrixPtr--;
}
