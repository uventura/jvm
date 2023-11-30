#ifndef JVM_RUNNER
#define JVM_RUNNER

#include "lib/base/class_file/class_file.h"
#include "lib/class_loader/class_file_list.h"

void jvm_runner(ClassFile *class_file, char *class_path);

void jvm_runner_get_file_path(char *dest, char *class_path);

#endif
