#include "lib/interpreter/opcodes_generic.h"

u2 get_branch_offset(MethodData *method_data)
{
    u2 branchbyte1 = method_data->code.code[method_data->pc + 1];
    u2 branchbyte2 = method_data->code.code[method_data->pc + 2];
    u2 offset = (branchbyte1 << 8) | branchbyte2;
    return offset-1;
}
