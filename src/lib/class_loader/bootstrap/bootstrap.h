#ifndef JVM_CLASS_LOADER_BOOTSTRAP
#define JVM_CLASS_LOADER_BOOTSTRAP

#include <stdio.h>

#include "lib/base/class_file/class_file.h"
#include "lib/base/class_file/cp_info.h"
#include "lib/base/class_file/field_info.h"

ClassFile load_class_file(const char *filepath);
void free_class_file(ClassFile class_file);

cp_info *load_constant_pool(FILE *file, u2 constant_pool_count);
u2 *load_interfaces(FILE *file, u2 interfaces_count);
field_info *load_field_info(FILE *file, u2 fields_count);

#endif
