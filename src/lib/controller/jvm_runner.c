#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/base/defines.h"
#include "lib/base/structures/stack.h"
#include "lib/class_loader/class_file_list.h"
#include "lib/class_loader/class_loader.h"
#include "lib/controller/jvm_runner.h"

void jvm_runner(ClassFile *class_file, char *class_path)
{
    // Get Path from Class File
    u4 path_size = strlen(class_path);
    char base_path[path_size];
    jvm_runner_get_file_path(base_path, class_path);

    // Stack Frame
    Stack stack_frame;
    stack_initialize(&stack_frame);

    // Recursive Load
    ClassFileList loaded_classes = class_file_list_init();
    class_loader_recursive(class_file, &loaded_classes, base_path);

    // Initialize
    class_loader_initialize(&loaded_classes, &stack_frame);

    // Run Main

    // Free Classes
    class_file_list_free(&loaded_classes);

    // Free Stack Frame
    free_stack(&stack_frame);
}

void jvm_runner_get_file_path(char *dest, char *class_path)
{
    u4 path_size = strlen(class_path);

    int32_t end_pos;
    for (end_pos = path_size - 1; end_pos >= 0; end_pos--)
    {
        if (class_path[end_pos] == '/')
        {
            break;
        }
    }

    for (int32_t pos = 0; pos <= end_pos; ++pos)
    {
        dest[pos] = class_path[pos];
    }

    dest[end_pos + 1] = '\0';
}
