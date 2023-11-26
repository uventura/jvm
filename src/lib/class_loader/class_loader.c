#include "lib/class_loader/class_loader.h"
#include "lib/base/class_file/class_file.h"
#include "lib/base/class_file/cp_info.h"
#include "lib/base/defines.h"
#include "lib/class_loader/class_file_list.h"

#include <string.h>

void class_loader_recursive(ClassFile *class_file, ClassFileList *list)
{
    char this_class_name[MAX_CLASS_NAME_SIZE];
    get_class_name(class_file->this_class, class_file->constant_pool, this_class_name);
    if(strcmp(this_class_name, "java/lang/Object") == 0)
    {
        return;
    }
    class_file_list_insert(list, class_file, this_class_name);

    char super_class_name[MAX_CLASS_NAME_SIZE];
    get_class_name(class_file->super_class, class_file->constant_pool, super_class_name);
    if(strcmp(super_class_name, "java/lang/Object") == 0)
    {
        return;
    }
}
