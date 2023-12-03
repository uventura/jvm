#include "lib/runtime_data_area/method_area.h"
#include "lib/base/class_file/method_info.h"
#include "lib/base/structures/stack.h"
#include "lib/runtime_data_area/frame.h"

#include <malloc.h>
#include <string.h>

// Delete includes below
#include <stdio.h>

void method_area_call_method(method_info *method, cp_info *constant_pool, Stack *stack_frame,
                             ClassFileList *loaded_classes)
{
    MethodData method_data;
    method_data.method = method;
    method_data.loaded_classes = loaded_classes;
    method_data.pc = 0;

    Frame new_frame;
    Stack operand_stack;
    frame_initialize(&new_frame, &operand_stack, constant_pool, method->attributes->info.code, stack_frame);
    stack_push(stack_frame, &new_frame);

    printf("Frame initialized");

    frame_free(&new_frame);
}

method_info *method_area_search_method(const char *method, ClassFile *class)
{
    for (u2 method_index = 0; method_index < class->methods_count; method_index++)
    {
        u2 name_index = class->methods[method_index].name_index;

        char method_name[200];
        get_utf8_value(name_index - 1, class->constant_pool, method_name);

        if (strcmp(method_name, method) == 0)
        {
            return &class->methods[method_index];
        }
    }

    return NULL;
}
