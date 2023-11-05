#ifndef JVM_CONTROLLER
#define JVM_CONTROLLER

#include "lib/base/class_file/cp_info.h"
#include "lib/base/defines.h"

int jvm_run(int argc, char **argv);

void jvm_read_class(char *class_file_path);
void jvm_run_class(char *class_file_path); // Not implemented yet

void jvm_display_constant_pool(cp_info *constant_pool, u2 constant_pool_count);

#endif
