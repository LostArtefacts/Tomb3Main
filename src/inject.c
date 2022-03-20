#include "inject.h"

#include "game/lara.h"
#include "inject_util.h"

void Inject_All(void)
{
    INJECT(0x00440DB0, Lara_AsForwardJump, 1);
}
