#ifndef JVM_INTERPRETER_FUNCTIONALITIES
#define JVM_INTERPRETER_FUNCTIONALITIES

#include "lib/base/defines.h"

typedef struct
{
    char **parameters;
    u2 size;
} MethodParameters;

MethodParameters get_parameters_string(char *descriptor_string);

#endif
