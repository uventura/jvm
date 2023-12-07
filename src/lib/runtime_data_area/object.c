#include "lib/runtime_data_area/object.h"
#include "lib/base/class_file/field_info.h"

#include <malloc.h>

JVMObject *object_init_dynamic(ClassFile *ref_class)
{
    JVMObject *object = (JVMObject *)malloc(sizeof(JVMObject));
    object->class = ref_class;
    object->data = (JVMObjectValue *)malloc(sizeof(JVMObjectValue) * ref_class->fields_count);

    u2 index;
    for (index = 0; index < ref_class->fields_count; index++)
    {
        object->data[index].field = ref_class->fields + index;
    }

    return object;
}

void object_dynamic_free(JVMObject *object)
{
    free(object->data);
}
