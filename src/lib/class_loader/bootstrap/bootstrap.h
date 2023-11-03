#ifndef JVM_CLASS_LOADER_BOOTSTRAP
#define JVM_CLASS_LOADER_BOOTSTRAP

#include <stdio.h>

#include "lib/base/class_file/class_file.h"

cp_info *load_constant_pool(FILE *file, u2 constant_pool_count);
ClassFile load_class_file(const char *filepath);
void free_class_file(ClassFile class_file);

#endif
