#ifndef JVM_GLOBALS
#define JVM_GLOBALS

#ifdef _WIN32
    #define JVM_WINDOWS "windows"
#else
    #define JVM_UNIX "unix"
#endif

#include "lib/environment/jvm_debug_functions.h"

extern u1 JVM_DEBUG_MODE_ACTIVE;

#endif
