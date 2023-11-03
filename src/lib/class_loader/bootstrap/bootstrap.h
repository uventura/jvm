#ifndef JVM_CLASS_LOADER_BOOTSTRAP
#define JVM_CLASS_LOADER_BOOTSTRAP

#include <stdio.h>

#include "lib/base/class_file/class_file.h"

ClassFile load_class_file(const char *filepath);

#endif
