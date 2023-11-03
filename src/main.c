#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/class_loader/bootstrap/bootstrap.h"

int main()
{
    ClassFile class_file = load_class_file("data/examples/HelloWorld.class");
    for (int i = 0; i < class_file.constant_pool_count; ++i)
    {
        const char *tag = get_info_name(class_file.constant_pool[i].tag);
        printf("%d %s\n", i, tag);
        if (strcmp(tag, "Utf8") == 0)
        {
            char element[100];
            memcpy(element, class_file.constant_pool[i].info.Utf8.bytes, class_file.constant_pool[i].info.Utf8.length);
            element[class_file.constant_pool[i].info.Utf8.length] = '\0';
            printf("\t%s\n", element);
        }
    }

    free_class_file(class_file);
}
