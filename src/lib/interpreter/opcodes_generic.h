#ifndef JVM_OPCODES_GENERIC
#define JVM_OPCODES_GENERIC

#include "lib/base/defines.h"
#include "lib/runtime_data_area/method_area.h"
#include "lib/runtime_data_area/frame.h"

u2 get_branch_offset(MethodData *method_data);
int get_branch_offset_int(MethodData *method_data);
int get_branch_offset_int_2(MethodData *method_data);

void dstore_generic(Frame* current_frame, u2 index);

#endif
