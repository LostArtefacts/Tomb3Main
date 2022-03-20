#include "inject.h"
#include "log.h"

#include <windows.h>

HINSTANCE hInstance = NULL;

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        Log_Init();
        LOG_INFO("attached");
        hInstance = hinstDLL;
        Inject_All();
        break;

    case DLL_PROCESS_DETACH:
        LOG_INFO("detached");
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;
    }

    return TRUE;
}
