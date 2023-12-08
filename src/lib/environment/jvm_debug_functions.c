#include "lib/environment/jvm_debug.h"

#include <stdarg.h>
#include <stdio.h>

u1 JVM_DEBUG_MODE_ACTIVE = FALSE;

void jvm_debug_print(const char *message, ...)
{
    if (JVM_DEBUG_MODE_ACTIVE)
    {
        va_list args;
        va_start(args, message);
        vprintf(message, args);
        va_end(args);
    }
}
