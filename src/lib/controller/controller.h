#ifndef JVM_CONTROLLER
#define JVM_CONTROLLER

#include "lib/base/class_file/class_file.h"
#include "lib/base/class_file/cp_info.h"
#include "lib/base/defines.h"

// Header with the prototypes for the main JVM functions and to display the bytecode.

int jvm_run(int argc, char **argv);

void jvm_read_class(char *class_file_path);
void jvm_run_class(char *class_file_path); // Not implemented yet

void jvm_display_general_information(ClassFile class_file);
void jvm_display_constant_pool(cp_info *constant_pool, u2 constant_pool_count);
void jvm_display_interfaces(u2 interfaces_count, u2 *interfaces, cp_info *constant_pool);
void jvm_display_fields(u2 fields_count, field_info *fields, cp_info *constant_pool);
void jvm_display_methods(u2 methods_count, method_info *methods, cp_info *constant_pool);
void jvm_display_attributes(u2 attributes_count, attribute_info *attributes, cp_info *constant_pool, u4 spaces_count);

void jvm_print_spaces(u4 spaces_count);

void jvm_display_specific_attributes_info(const char *type, attribute_info *attribute, cp_info *constant_pool,
                                          u4 spaces_count);
void jvm_display_attrib_code(attribute_info *attribute, cp_info *constant_pool, u4 spaces_count);
void jvm_display_attrib_source_file(attribute_info *attribute, cp_info *constant_pool, u4 spaces_count);
void jvm_display_attrib_constant_value(attribute_info *attribute, cp_info *constant_pool, u4 spaces_count);
void jvm_display_attrib_exceptions(attribute_info *attribute, cp_info *constant_pool, u4 spaces_count);
void jvm_display_attrib_synthetic(attribute_info *attribute, cp_info *constant_pool, u4 spaces_count);
void jvm_display_attrib_inner_classes(attribute_info *attribute, cp_info *constant_pool, u4 spaces_count);

#endif
