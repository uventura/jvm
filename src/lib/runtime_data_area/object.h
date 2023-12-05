#ifndef JVM_OBJECT_REPRESENTATION
#define JVM_OBJECT_REPRESENTATION

#include "lib/base/class_file/class_file.h"
#include "lib/base/class_file/field_info.h"

typedef struct
{
    void *value;
    field_info *field;
} JVMObjectValue;

typedef struct
{
    ClassFile *class;
    JVMObjectValue *data;
} JVMObject;

JVMObject *object_init_dynamic(ClassFile *ref_class);

#endif
