#include "game/random.h"

#include "global/vars.h"

int32_t Random_GetControl(void)
{
    g_RandControl = 0x41C64E6D * g_RandControl + 12345;
    return (g_RandControl >> 10) & 0x7FFF;
}
