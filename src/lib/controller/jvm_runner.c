#include <stdlib.h>

#include "lib/controller/jvm_runner.h"

void jvm_runner(ClassFile *class_file, char *class_path)
{
    char *absolute_path = realpath(class_path, NULL);
    printf("%s\n", absolute_path);
}
