#include "game/text.h"

#include "global/const.h"
#include "global/stubs.h"
#include "global/vars.h"

#include <string.h>

#define TEXT_SCALE_NEUTRAL (1 << 16)

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
    result->scale.v = TEXT_SCALE_NEUTRAL;
    result->scale.h = TEXT_SCALE_NEUTRAL;
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
    Text_Change(result, string);
    g_TextstringCount++;

    return result;
}

void Text_Change(struct TEXTSTRING *txt, const char *string)
{
    if (!string || !txt->flags.active) {
        return;
    }
    size_t length = strlen(string) + 1;
    strncpy(txt->string, string, TEXT_MAX_STRING_SIZE - 1);
    if (length >= TEXT_MAX_STRING_SIZE) {
        txt->string[TEXT_MAX_STRING_SIZE - 1] = '\0';
    }
}

void Text_Flash(struct TEXTSTRING *txt, bool enable, int16_t rate)
{
    if (!txt) {
        return;
    }
    if (enable) {
        txt->flags.flash = 1;
        txt->flash.rate = rate;
        txt->flash.count = rate;
    } else {
        txt->flags.flash = 0;
    }
}

void Text_AddBackground(
    struct TEXTSTRING *txt, int16_t w, int16_t h, int16_t x, int16_t y,
    int16_t z, int16_t colour, uint16_t *gourptr, uint16_t flags)
{
    if (!txt) {
        return;
    }
    uint32_t scale_h = Text_GetScaleH(txt->scale.h);
    uint32_t scale_v = Text_GetScaleV(txt->scale.v);
    txt->flags.background = 1;
    txt->bgnd_size.x = (w * scale_h) / TEXT_SCALE_NEUTRAL;
    txt->bgnd_size.y = (h * scale_v) / TEXT_SCALE_NEUTRAL;
    txt->bgnd_off.x = (x * scale_h) / TEXT_SCALE_NEUTRAL;
    txt->bgnd_off.y = (y * scale_v) / TEXT_SCALE_NEUTRAL;
    txt->bgnd_off.z = z;
    txt->bgnd_gour = gourptr;
    txt->bgnd_colour = colour;
    txt->bgnd_flags = flags;
}

void Text_RemoveBackground(struct TEXTSTRING *txt)
{
    if (!txt) {
        return;
    }
    txt->flags.background = 0;
}

void Text_AddOutline(
    struct TEXTSTRING *txt, bool enable, int16_t colour, uint16_t *gourptr,
    uint16_t flags)
{
    if (!txt) {
        return;
    }
    txt->flags.outline = 1;
    txt->outl_gour = gourptr;
    txt->outl_colour = colour;
    txt->outl_flags = flags;
}

void Text_RemoveOutline(struct TEXTSTRING *txt)
{
    if (!txt) {
        return;
    }
    txt->flags.outline = 0;
}

void Text_CentreH(struct TEXTSTRING *txt, bool enable)
{
    if (!txt) {
        return;
    }
    txt->flags.centre_h = enable ? 1 : 0;
}

void Text_CentreV(struct TEXTSTRING *txt, bool enable)
{
    if (!txt) {
        return;
    }
    txt->flags.centre_v = enable ? 1 : 0;
}

void Text_AlignRight(struct TEXTSTRING *txt, bool enable)
{
    if (!txt) {
        return;
    }
    txt->flags.right_align = enable ? 1 : 0;
}

void Text_AlignBottom(struct TEXTSTRING *txt, bool enable)
{
    if (!txt) {
        return;
    }
    txt->flags.bottom_align = enable ? 1 : 0;
}

int32_t Text_GetWidth(struct TEXTSTRING *txt)
{
    if (!txt) {
        return 0;
    }
    uint32_t width = 0;
    uint32_t scale_h = Text_GetScaleH(txt->scale.h);
    char *string = txt->string;
    while (*string) {
        uint8_t letter = *string++;
        if (letter == 0x11 || letter == 0x12) {
            width += 14;
            continue;
        }

        if (letter > 0x81) {
            continue;
        }
        if (letter > '\n' && letter < ' ') {
            continue;
        }
        if (letter == '(' || letter == ')' || letter == '$' || letter == '~') {
            continue;
        }

        if (letter == ' ') {
            width += (scale_h * txt->word_spacing) / TEXT_SCALE_NEUTRAL;
            continue;
        }

        if (letter >= 0x7F) {
            width += (16 * scale_h) / TEXT_SCALE_NEUTRAL;
            continue;
        }

        uint8_t sprite_num;
        if (letter >= 0x0B) {
            sprite_num = g_TextASCIIMap[letter];
        } else {
            sprite_num = letter + 81;
        }

        if (sprite_num < '0' || sprite_num > '9') {
            width +=
                (scale_h * (txt->letter_spacing + g_TextSpacing[sprite_num]))
                / TEXT_SCALE_NEUTRAL;
        } else {
            width += (12 * scale_h) / TEXT_SCALE_NEUTRAL;
        }
    }

    width -= txt->letter_spacing;
    width &= 0xFFFE;
    return width;
}
