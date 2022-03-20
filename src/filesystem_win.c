#include "filesystem.h"

#include "memory.h"

#include <assert.h>
#include <shlwapi.h>
#include <windows.h>

const char *File_GetGameDirectory(void)
{
    size_t buf_size = MAX_PATH;
    char *buf = Memory_Alloc(buf_size);
    DWORD result = GetModuleFileName(NULL, buf, buf_size);
    // TODO: too lazy to do a rolling buffer
    assert(result);
    PathRemoveFileSpec(buf);
    return buf;
}
