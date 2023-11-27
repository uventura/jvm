#include "lib/class_loader/class_loader.h"
#include "lib/base/class_file/class_file.h"
#include "lib/base/class_file/cp_info.h"
#include "lib/base/defines.h"
#include "lib/class_loader/bootstrap/bootstrap.h"
#include "lib/class_loader/class_file_list.h"

#include <malloc.h>
#include <string.h>
#include <stdio.h>

void class_loader_recursive(ClassFile *class_file, ClassFileList *list, char *class_path)
{
    char this_class_name[MAX_CLASS_NAME_SIZE];

    get_class_name(class_file->this_class, class_file->constant_pool, this_class_name);
    if (strcmp(this_class_name, "java/lang/Object") == 0)
    {
        return;
    }
    class_file_list_insert(list, class_file, this_class_name);

    char super_class_name[MAX_CLASS_NAME_SIZE];
    get_class_name(class_file->super_class, class_file->constant_pool, super_class_name);
    if (strcmp(super_class_name, "java/lang/Object") == 0)
    {
        return;
    }

    char super_class_path[MAX_CLASS_NAME_SIZE] = "";
    strcpy(super_class_path, class_path);
    strcat(super_class_path, super_class_name);
    strcat(super_class_path, ".class");

    ClassFile *super_class_file = (ClassFile *)malloc(sizeof(ClassFile));
    *super_class_file = load_class_file(super_class_path);
    class_loader_recursive(super_class_file, list, class_path);
}

void class_loader_initialize(ClassFileList *classes)
{
    // Here we should call initialize functionalities
    printf("This class: %d\n", classes->head->class->this_class);
}
