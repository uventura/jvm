#ifndef JVM_CONTROLLER
#define JVM_CONTROLLER

#include "lib/base/defines.h"

int jvm_run(int argc, char **argv);

void jvm_read_class(char *class_file_path);
void jvm_run_class(char *class_file_path); // Not implemented yet

#endif
