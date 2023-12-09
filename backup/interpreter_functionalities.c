#include "lib/interpreter/interpreter_functionalities.h"

MethodParameters get_parameters_string(char *descriptor_string)
{
    MethodParameters parameters;
    u4 pos = 1;
    u1 is_class = FALSE;

    while (descriptor_string[pos] != ')')
    {
        if (descriptor_string[pos] == 'L')
        {
            is_class = TRUE;
        }
        else
        {
        }
    }
    return parameters;
}
