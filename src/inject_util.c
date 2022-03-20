#include "inject_util.h"

#include "log.h"

#include <windows.h>

#pragma pack(push, 1)
typedef struct {
    uint8_t opcode; // must be 0xE9
    uint32_t offset;
} JMP;
#pragma pack(pop)

void InjectImpl(void (*from)(void), void (*to)(void), bool enable)
{
    if (from == to) {
        return;
    }

    if (!enable) {
        void (*aux)(void) = from;
        from = to;
        to = aux;
    }

    DWORD tmp;
    LOG_DEBUG("Patching %p to %p", from, to);
    VirtualProtect(from, sizeof(JMP), PAGE_EXECUTE_READWRITE, &tmp);
    HANDLE hCurrentProcess = GetCurrentProcess();
    JMP buf;
    buf.opcode = 0xE9;
    buf.offset = (DWORD)(to) - ((DWORD)(from) + sizeof(JMP));
    WriteProcessMemory(hCurrentProcess, from, &buf, sizeof(JMP), &tmp);
    CloseHandle(hCurrentProcess);
}
