#ifndef JVM_ARRAY
#define JVM_ARRAY

#define T_BOOLEAN 4
#define T_CHAR 5
#define T_FLOAT 6
#define T_DOUBLE 7
#define T_BYTE 8
#define T_SHORT 9
#define T_INT 0
#define T_LONG 1

#include "lib/base/defines.h"

typedef struct
{
    u1 type;
    void *array;
    u2 size;
} JVMArray;

#endif
