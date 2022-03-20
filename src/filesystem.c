#include "filesystem.h"

#include "memory.h"

#include <stdio.h>
#include <string.h>

static bool File_ExistsRaw(const char *path);

static bool File_ExistsRaw(const char *path)
{
    FILE *fp = fopen(path, "rb");
    if (fp) {
        fclose(fp);
        return true;
    }
    return false;
}

bool File_IsAbsolute(const char *path)
{
    return path && (path[0] == '/' || strstr(path, ":\\"));
}

bool File_IsRelative(const char *path)
{
    return path && !File_IsAbsolute(path);
}

char *File_GetFullPath(const char *path)
{
    if (!File_ExistsRaw(path) && File_IsRelative(path)) {
        const char *game_dir = File_GetGameDirectory();
        if (game_dir) {
            size_t out_size = strlen(game_dir) + strlen(path) + 2;
            char *out = Memory_Alloc(out_size);
            sprintf(out, "%s/%s", game_dir, path);
            return out;
        }
    }
    return Memory_DupStr(path);
}
