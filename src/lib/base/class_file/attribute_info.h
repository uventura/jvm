#ifndef JVM_ATTRIBUTE_INFO
#define JVM_ATTRIBUTE_INFO

#include "lib/base/defines.h"

typedef struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u1 *info;
} attribute_info;

#endif
