#ifndef JVM_CLASS_DEFINES
#define JVM_CLASS_DEFINES

#include "lib/base/defines.h"

// Header defining the different access flags and constant pool tags, as well as the prototypes for functions to get
// then.

// Access Flags
#define ACC_PUBLIC 0x0001
#define ACC_PRIVATE 0x0002
#define ACC_PROTECTED 0x0004
#define ACC_STATIC 0x0008
#define ACC_FINAL 0x0010
#define ACC_VOLATILE 0x0040
#define ACC_TRANSIENT 0x0080
#define ACC_SYNTHETIC 0x1000
#define ACC_ENUM 0x4000

const char *get_access_flag_name(u2 id);

// Constant Pool Tags
#define CONSTANT_Class 7
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String 8
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_NameAndType 12
#define CONSTANT_Utf8 1
#define CONSTANT_MethodHandle 15
#define CONSTANT_InvokeDynamic 18

const char *get_cp_info_name(u2 id);

#endif
