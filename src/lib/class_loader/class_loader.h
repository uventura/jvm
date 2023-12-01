#ifndef JVM_CLASS_LOADER
#define JVM_CLASS_LOADER

#include "lib/base/class_file/class_file.h"
#include "lib/base/structures/stack.h"
#include "lib/class_loader/class_file_list.h"

void class_loader_recursive(ClassFile *class_file, ClassFileList *list, char *class_path);
void class_loader_initialize(ClassFileList *classes, Stack *stack_frame);
Stack class_loader_stack_cinit_classes(ClassFileList *classes);

#endif
