#include "game/text.h"

#include "global/const.h"
#include "global/stubs.h"
#include "global/vars.h"

#include <string.h>

void Text_Init(void)
{
    Overlay_DisplayModeInfo(NULL);

    for (int i = 0; i < TEXT_MAX_STRINGS; i++) {
        g_TextstringTable[i].flags.all = 0;
    }
    g_TextstringCount = 0;
}

struct TEXTSTRING *Text_Create(
    int32_t x, int32_t y, int32_t colour, const char *string)
{
    if (!string) {
        return NULL;
    }

    if (g_TextstringCount >= TEXT_MAX_STRINGS) {
        return NULL;
    }

    struct TEXTSTRING *result = &g_TextstringTable[0];
    int n;
    for (n = 0; n < TEXT_MAX_STRINGS; n++) {
        if (!result->flags.active) {
            break;
        }
        result++;
    }
    if (n >= TEXT_MAX_STRINGS) {
        return NULL;
    }

    result->string = g_TextstringBuffers[n];
    result->pos.x = x;
    result->pos.y = y;
    result->pos.z = 0;
    result->scale.v = DEG_1;
    result->scale.h = DEG_1;
    result->colour = colour;
    result->letter_spacing = 0;
    result->word_spacing = 6;
    result->text_flags = 0;
    result->outl_flags = 0;
    result->bgnd_flags = 0;
    result->bgnd_size.x = 0;
    result->bgnd_size.y = 0;
    result->bgnd_off.x = 0;
    result->bgnd_off.y = 0;
    result->bgnd_off.z = 0;
    result->flags.all = 0;
    result->flags.active = 1;
    int32_t length = Text_GetLength(string);
    if (length >= TEXT_MAX_STRING_SIZE) {
        length = TEXT_MAX_STRING_SIZE - 1;
    }
    memcpy(result->string, string, length + 1);
    g_TextstringCount++;

    return result;
}
