#ifndef JVM_CLASS_LOADER_BOOTSTRAP
#define JVM_CLASS_LOADER_BOOTSTRAP

#include <stdio.h>

#include "lib/base/class_file/attribute_info.h"
#include "lib/base/class_file/class_file.h"
#include "lib/base/class_file/cp_info.h"
#include "lib/base/class_file/field_info.h"
#include "lib/base/class_file/method_info.h"

// Header with the prototypes for the functions to load the ".class" file bytecode and to free the allocated memory
// afterwards.

ClassFile load_class_file(const char *filepath);
void free_class_file(ClassFile class_file);

cp_info *load_constant_pool(FILE *file, u2 constant_pool_count);
void free_constant_pool(u2 constant_pool_count, cp_info *constant_pool);

u2 *load_interfaces(FILE *file, u2 interfaces_count);
void free_interfaces(u2 interfaces_count, u2 *interfaces);

field_info *load_field_info(FILE *file, u2 fields_count, cp_info *constant_pool);
void free_fields(u2 field_count, field_info *fields, cp_info *constant_pool);

method_info *load_method_info(FILE *file, u2 method_count, cp_info *constant_pool);
void free_methods(u2 methods_count, method_info *methods, cp_info *constant_pool);

attribute_info *load_attribute_info(FILE *file, u2 attributes_count, cp_info *constant_pool);
attributes_type_info load_attribute_type(FILE *file, const char *type, cp_info *constant_pool, u4 attributes_length);
void free_attributes(u2 attributes_count, attribute_info *attributes, cp_info *constant_pool);

#endif
