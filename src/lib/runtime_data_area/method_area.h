#ifndef JVM_METHOD_AREA
#define JVM_METHOD_AREA

#include "lib/base/class_file/attribute_info.h"
#include "lib/base/class_file/cp_info.h"
#include "lib/base/class_file/method_info.h"
#include "lib/base/defines.h"
#include "lib/base/structures/stack.h"
#include "lib/class_loader/class_file_list.h"

typedef struct
{
    Stack *frame_stack;
    method_info *method;
    ClassFileList *loaded_classes;
    u8 pc;
    Code_attribute code; // Just to improve the usability, but you can access in "*method"
} MethodData;

void method_area_call_method(method_info *method, cp_info *constant_pool, Stack *stack_frame,
                             ClassFileList *loaded_classes);
method_info *method_area_search_method(const char *method, ClassFile *class);

#endif
