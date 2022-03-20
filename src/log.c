#include "log.h"

#include <stdarg.h>
#include <stdio.h>

FILE *m_LogHandle = NULL;

void Log_Init(void)
{
    char *full_path = "Tomb3Main.log";
    m_LogHandle = fopen(full_path, "w");
}

void Log_Message(
    const char *file, int line, const char *func, const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);

    // print to stdout
    printf("%s %d %s ", file, line, func);
    vprintf(fmt, va);
    printf("\n");
    fflush(stdout);

    if (m_LogHandle) {
        // now print the same to the log file
        fprintf(m_LogHandle, "%s %d %s ", file, line, func);
        vfprintf(m_LogHandle, fmt, va);
        fprintf(m_LogHandle, "\n");
        fflush(m_LogHandle);
    }

    va_end(va);
}

void Log_Shutdown(void)
{
    if (m_LogHandle) {
        fclose(m_LogHandle);
        m_LogHandle = NULL;
    }
}
