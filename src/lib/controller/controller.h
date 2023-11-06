#ifndef JVM_CONTROLLER
#define JVM_CONTROLLER

#include "lib/base/class_file/class_file.h"
#include "lib/base/class_file/cp_info.h"
#include "lib/base/defines.h"

int jvm_run(int argc, char **argv);

void jvm_read_class(char *class_file_path);
void jvm_run_class(char *class_file_path); // Not implemented yet

void jvm_display_general_information(ClassFile class_file);
void jvm_display_constant_pool(cp_info *constant_pool, u2 constant_pool_count);
void jvm_display_fields(u2 fields_count, field_info *fields, cp_info *constant_pool);
void jvm_display_methods(u2 methods_count, method_info *methods, cp_info *constant_pool);
void jvm_display_attributes(u2 attributes_count, attribute_info *attributes, cp_info *constant_pool);

#endif
