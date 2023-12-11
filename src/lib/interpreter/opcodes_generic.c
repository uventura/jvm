#include "lib/interpreter/opcodes_generic.h"

u2 get_branch_offset(MethodData *method_data)
{
    u2 branchbyte1 = method_data->code.code[method_data->pc + 1];
    u2 branchbyte2 = method_data->code.code[method_data->pc + 2];
    u2 offset = (branchbyte1 << 8) | branchbyte2;
    return offset - 1;
}

int get_branch_offset_int(MethodData *method_data)
{
    char branchbyte1 = (char)method_data->code.code[method_data->pc + 1];
    char branchbyte2 = (char)method_data->code.code[method_data->pc + 2];
    u4 offset_un = (branchbyte1 << 8) | branchbyte2;
    int offset = offset_un;
    return offset - 1;
}
