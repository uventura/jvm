#ifndef JVM_METHOD_FRAME
#define JVM_METHOD_FRAME

#include "lib/base/class_file/attribute_info.h"
#include "lib/base/class_file/cp_info.h"
#include "lib/base/structures/stack.h"

typedef struct
{
    cp_info *constant_pool;
    Stack *operand_stack;
    void **local_variables;
} Frame;

void frame_initialize(Frame *frame, Stack *operand_stack, cp_info *constant_pool, Code_attribute code,
                      Stack *stack_frame);

void frame_free(Frame *frame);

#endif
