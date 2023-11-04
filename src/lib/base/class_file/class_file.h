#ifndef JVM_CLASS_FILE
#define JVM_CLASS_FILE

#include "lib/base/class_file/cp_info.h"
#include "lib/base/class_file/field_info.h"
#include "lib/base/defines.h"

typedef struct
{
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    cp_info *constant_pool;
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2 *interfaces;
    u2 fields_count;
    field_info *fields;
    u2 methods_count;
    // method_info *methods;
    u2 attributes_count;
    // attribute_info *attributes;
} ClassFile;

#endif
