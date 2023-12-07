#ifndef JVM_METHOD_INFO
#define JVM_METHOD_INFO

#include "lib/base/class_file/attribute_info.h"
#include "lib/base/class_file/class_defines.h"
#include "lib/base/defines.h"

// Method Descriptors
#define VOID_TYPE 'V'
#define INT_TYPE 'I'
#define LONG_TYPE 'J'
#define FLOAT_TYPE 'F'
#define DOUBLE_TYPE 'D'
#define BYTE_TYPE 'B'
#define SHORT_TYPE 'S'
#define CHAR_TYPE 'C'
#define BOOLEAD_TYPE 'Z'
#define CLASS_TYPE 'L'

// Header defining the struct for methods.

typedef struct
{
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes;
} method_info;

#endif
