#ifndef JVM_FIELD_INFO
#define JVM_FIELD_INFO

#include "lib/base/class_file/attribute_info.h"
#include "lib/base/class_file/class_defines.h"
#include "lib/base/defines.h"

// Reference: https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html#jvms-4.5
//            https://docs.oracle.com/javase/specs/jvms/se8/html/jvms-4.html#jvms-4.7

// Header defining the struct for fields.

typedef struct
{
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes;
} field_info;

#endif
