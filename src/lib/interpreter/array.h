#ifndef JVM_ARRAY
#define JVM_ARRAY

#define T_BOOLEAN 4
#define T_CHAR 5
#define T_FLOAT 6
#define T_DOUBLE 7
#define T_BYTE 8
#define T_SHORT 9
#define T_INT 10
#define T_LONG 11

#include "lib/base/defines.h"

typedef struct
{
    void* array;
    u4 size;
} JVMArray;


#endif
