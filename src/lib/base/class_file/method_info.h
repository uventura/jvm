#ifndef JVM_METHOD_INFO
#define JVM_METHOD_INFO

#include "lib/base/class_file/attribute_info.h"
#include "lib/base/class_file/class_defines.h"
#include "lib/base/defines.h"

typedef struct
{
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes;
} method_info;

#endif
