#ifndef JVM_READ_FILE
#define JVM_READ_FILE

#include "lib/base/defines.h"
#include <stdio.h>

// Header with the prototypes for the functions utilized to read different integer types.

u1 u1_read(FILE *file);
u2 u2_read(FILE *file);
u4 u4_read(FILE *file);

#endif
