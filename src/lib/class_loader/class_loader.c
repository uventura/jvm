#include "lib/class_loader/class_loader.h"
#include "lib/base/class_file/class_file.h"
#include "lib/base/class_file/cp_info.h"
#include "lib/base/class_file/method_info.h"
#include "lib/base/defines.h"
#include "lib/base/structures/stack.h"
#include "lib/class_loader/bootstrap/bootstrap.h"
#include "lib/class_loader/class_file_list.h"
#include "lib/runtime_data_area/method_area.h"

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Exclude the include below
#include "lib/controller/jvm_reader.h"

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

// Class Loader Initialize
//  Here we call all <clinit> from classes
void class_loader_initialize(ClassFileList *classes, Stack *stack_frame)
{
    Stack clinit_classes;
    class_loader_stack_cinit_classes(&clinit_classes, classes);

    while (!stack_is_empty(&clinit_classes))
    {
        ClassFile *class = (ClassFile *)stack_top(&clinit_classes);
        method_info *init_method = method_area_search_method("<clinit>", class);

        if (init_method == NULL)
        {
            stack_pop(&clinit_classes);
            continue;
        }

        method_area_call_method(init_method, class->constant_pool, stack_frame, classes);

        stack_pop(&clinit_classes);
    }

    free_stack(&clinit_classes);
}

void class_loader_stack_cinit_classes(Stack *clinit_classes, ClassFileList *classes)
{
    stack_initialize(clinit_classes);

    ClassFile *main_class = classes->head->class;
    stack_push(clinit_classes, main_class);

    char super_class_name[MAX_CLASS_NAME_SIZE];
    get_class_name(main_class->super_class, main_class->constant_pool, super_class_name);

    while (strcmp(super_class_name, "java/lang/Object") != 0)
    {
        ClassFile *super_class = class_file_list_get(classes, super_class_name);
        if (super_class == NULL)
        {
            printf("[ERROR] Initialization Step: The Class '%s' wasn't loaded.\n", super_class_name);
            exit(EXIT_FAILURE);
        }
        stack_push(clinit_classes, super_class);

        get_class_name(super_class->super_class, super_class->constant_pool, super_class_name);
    }
}
