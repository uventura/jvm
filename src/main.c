#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/class_loader/bootstrap/bootstrap.h"
#include "lib/base/class_file/class_defines.h"

int main()
{
    ClassFile class_field = load_class_file("data/examples/Fields.class");
    for(int i = 0; i < class_field.fields_count; ++i)
    {
        printf("%d\n", class_field.fields[i].access_flags);
        printf("%d\n", class_field.fields[i].name_index);
        printf("%d\n", class_field.fields[i].descriptor_index);
    }
    free_class_file(class_field);
}
