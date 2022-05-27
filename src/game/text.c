#include "game/text.h"

#include "global/const.h"
#include "global/stubs.h"
#include "global/types.h"
#include "global/vars.h"

void Text_Init(void)
{
    Overlay_DisplayModeInfo(NULL);

    for (int i = 0; i < TEXT_MAX_STRINGS; i++) {
        g_TextstringTable[i].flags = 0;
    }
    g_TextstringCount = 0;
}
