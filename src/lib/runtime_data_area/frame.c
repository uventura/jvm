#include "lib/runtime_data_area/frame.h"

#include "lib/base/class_file/attribute_info.h"
#include "lib/base/class_file/cp_info.h"
#include "lib/base/defines.h"
#include "lib/base/structures/stack.h"
#include "lib/environment/jvm_debug.h"

#include <stdlib.h>

void frame_initialize(Frame *frame, Stack *operand_stack, cp_info *constant_pool, Code_attribute code,
                      Stack *stack_frame)
{
    // For Debugging Purposes
    jvm_debug_print("\t...Constructing frame...\n");

    frame->constant_pool = constant_pool;
    frame->local_variables = NULL;

    stack_initialize(operand_stack);
    frame->operand_stack = operand_stack;
    jvm_debug_print("\tCreating operand stack with sizeof: %d\n", code.max_stack);

    if (code.max_locals != 0)
    {
        frame->local_variables = (void **)calloc(code.max_locals + 1, sizeof(void *));
        jvm_debug_print("\tCreating local variables with sizeof: %d\n", code.max_locals);
        frame->max_locals = code.max_locals;
    }

    if (!stack_is_empty(stack_frame))
    {
        Frame *current_frame = (Frame *)stack_top(stack_frame);
        Stack *operands = current_frame->operand_stack;
        for (u2 local_index = 0; local_index < code.max_locals; ++local_index)
        {
            void *value = stack_top(operands);
            jvm_debug_print("\tPtr to local variable[%d]: %p\n", code.max_locals - local_index - 1, value);
            frame->local_variables[code.max_locals - local_index - 1] = stack_top(operands);
            stack_pop(operands);
        }
    }
    jvm_debug_print("\t........................\n");
}

void frame_free(Frame *frame)
{
    // free(frame->local_variables);

    while (!stack_is_empty(frame->operand_stack))
    {
        // free(stack_top(frame->operand_stack));
        stack_pop(frame->operand_stack);
    }
    jvm_debug_print("\t........................\n");
}
