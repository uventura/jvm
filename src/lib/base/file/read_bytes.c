#include "lib/base/file/read_bytes.h"

u2 u2_read(FILE *file)
{
    u2 value = getc(file);
    value = (value << 8) | (getc(file));
    return value;
}

u4 u4_read(FILE *file)
{
    u4 word = (u2_read(file) << 16) | u2_read(file);
    return word;
}
