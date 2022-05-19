#include "game/random.h"

static int32_t m_RandControl = 0xD371F947;

void Random_SeedControl(int32_t seed)
{
    m_RandControl = seed;
}

int32_t Random_GetControl(void)
{
    m_RandControl = 0x41C64E6D * m_RandControl + 12345;
    return (m_RandControl >> 10) & 0x7FFF;
}
