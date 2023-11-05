#include <stdio.h>
#include <string.h>

#include "lib/base/class_file/cp_info.h"

void get_utf8_value(u2 index, cp_info *constant_pool, char *buffer)
{
    memcpy((void*)buffer, constant_pool[index - 1].info.Utf8.bytes, constant_pool[index - 1].info.Utf8.length);
    buffer[constant_pool[index - 1].info.Utf8.length] = '\0';
}
