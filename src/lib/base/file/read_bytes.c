#include <stdio.h>

#include "lib/base/file/read_bytes.h"

// Reads a single byte from the ".class" file.
u1 u1_read(FILE *file)
{
    return getc(file);
}

// Reads two bytes from the ".class" file, concatenating then.
u2 u2_read(FILE *file)
{
    u2 value = getc(file);
    value = (value << 8) | (getc(file));
    return value;
}

// Reads four bytes from the ".class" file, concatenating then.
u4 u4_read(FILE *file)
{
    u4 half1 = u2_read(file);
    u4 half2 = u2_read(file);
    u4 word = (half1 << 16) | half2;
    return word;
}
