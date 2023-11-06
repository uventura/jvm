#ifndef JVM_CP_INFO
#define JVM_CP_INFO

// Reference: https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html#jvms-4.4

#include "lib/base/class_file/class_defines.h"
#include "lib/base/defines.h"

// Header defining structs that represent "constant_pool" types.

typedef struct
{
    u2 name_index;
} CONSTANT_Class_info;

typedef struct
{
    u2 class_index;
    u2 name_and_type_index;
} CONSTANT_Fieldref_info;

typedef struct
{
    u2 class_index;
    u2 name_and_type_index;
} CONSTANT_Methodref_info;

typedef struct
{
    u2 class_index;
    u2 name_and_type_index;
} CONSTANT_InterfaceMethodref_info;

typedef struct
{
    u2 string_index;
} CONSTANT_String_info;

typedef struct
{
    u4 bytes;
} CONSTANT_Integer_info;

typedef struct
{
    u4 bytes;
} CONSTANT_Float_info;

typedef struct
{
    u4 high_bytes;
    u4 low_bytes;
} CONSTANT_Long_info;

typedef struct
{
    u4 high_bytes;
    u4 low_bytes;
} CONSTANT_Double_info;

typedef struct
{
    u2 name_index;
    u2 descriptor_index;
} CONSTANT_NameAndType_info;

typedef struct
{
    u2 length;
    u1 *bytes;
} CONSTANT_Utf8_info;

typedef struct
{
    u1 tag;
    union {
        CONSTANT_Class_info Class;
        CONSTANT_Fieldref_info Fieldref;
        CONSTANT_Methodref_info Methodref;
        CONSTANT_InterfaceMethodref_info InterfaceMethodref;
        CONSTANT_String_info String;
        CONSTANT_Integer_info Integer;
        CONSTANT_Float_info Float;
        CONSTANT_Long_info Long;
        CONSTANT_Double_info Double;
        CONSTANT_NameAndType_info NameAndType;
        CONSTANT_Utf8_info Utf8;
    } info;
} cp_info;

const char *get_info_name(u2 id);

#endif
