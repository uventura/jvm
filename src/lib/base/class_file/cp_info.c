#include <stdio.h>
#include <string.h>

#include "lib/base/class_file/cp_info.h"

// Function to copy UTF-8 bytes in string.
void get_utf8_value(u2 index, cp_info *constant_pool, char *buffer)
{
    memcpy((void *)buffer, constant_pool[index].info.Utf8.bytes, constant_pool[index].info.Utf8.length);
    buffer[constant_pool[index].info.Utf8.length] = '\0';
}
