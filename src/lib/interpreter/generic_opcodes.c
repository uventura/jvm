#include "lib/interpreter/generic_opcodes.h"

#include <malloc.h>

u4* generic_fload(u2 index, Frame* frame)
{
    cp_info *value = frame->local_variables[2];
    u4 *float_value = (u4 *)malloc(sizeof(u4));
    *float_value = value->info.Float.bytes;

    return float_value;
}
