#include "lib/interpreter/byte_code.h"
#include "lib/base/math/iee754.h"
#include "lib/base/structures/stack.h"
#include "lib/class_loader/bootstrap/bootstrap.h"
#include "lib/class_loader/class_file_list.h"
#include "lib/environment/jvm_debug.h"
#include "lib/runtime_data_area/frame.h"
#include "lib/runtime_data_area/method_area.h"

#include <malloc.h>
#include <stdio.h>
#include <string.h>

// Exclude later
#include "lib/controller/jvm_reader.h"

// Functions for the opcode.

// 0x00
void nop(MethodData *method_data)
{
    // Nao faz nada.
}
// 0x01
void aconst_null(MethodData *method_data)
{
    // Colocar a referencia de objeto "NULL" na pilha de operandos.
    // Observacao: a JVM nao obriga um valor concreto para "NULL".
}
// 0x02
void iconst_m1(MethodData *method_data)
{
    // Colocar a constante inteira -1 na pilha de operandos.
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int *m1 = malloc(sizeof(int));
    *m1 = -1;
    stack_push(current_frame->operand_stack, m1);
}
// 0x03
void iconst_0(MethodData *method_data)
{
    // Colocar a constante inteira 0 na pilha de operandos.
Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int *m1 = malloc(sizeof(int));
    *m1 = 0;
    stack_push(current_frame->operand_stack, m1);
}
// 0x04
void iconst_1(MethodData *method_data)
{
    // Colocar a constante inteira 1 na pilha de operandos.
Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int *m1 = malloc(sizeof(int));
    *m1 = 1;
    stack_push(current_frame->operand_stack, m1);
}
// 0x05
void iconst_2(MethodData *method_data)
{
    // Colocar a constante inteira 2 na pilha de operandos.
Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int *m1 = malloc(sizeof(int));
    *m1 = 2;
    stack_push(current_frame->operand_stack, m1);
}
// 0x06
void iconst_3(MethodData *method_data)
{
    // Colocar a constante interia 3 na pilha de operandos.
Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int *m1 = malloc(sizeof(int));
    *m1 = 3;
    stack_push(current_frame->operand_stack, m1);
}
// 0x07
void iconst_4(MethodData *method_data)
{
    // Colocar a constante inteira 4 na pilha de operandos.
Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int *m1 = malloc(sizeof(int));
    *m1 = 4;
    stack_push(current_frame->operand_stack, m1);
}
// 0x08
void iconst_5(MethodData *method_data)
{
    // Colocar a constante inteira 5 na pilha de operandos.
Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int *m1 = malloc(sizeof(int));
    *m1 = 5;
    stack_push(current_frame->operand_stack, m1);
}
// 0x09
void lconst_0(MethodData *method_data)
{
    // Colocar a constante long 0 na pilha de operandos.
    // Usa 2 espacos na pilha.
}
// 0x0A
void lconst_1(MethodData *method_data)
{
    // Colocar a constante long 1 na pilha de operandos.
    // Usa 2 espacos na pilha.
}
// 0x0B
void fconst_0(MethodData *method_data)
{
    // Colocar a constante float 0.0 na pilha de operandos.
}
// 0x0C
void fconst_1(MethodData *method_data)
{
    // Colocar a constante float 1.0 na pilha de operandos.
}
// 0x0D
void fconst_2(MethodData *method_data)
{
    // Colocar a constante float 2.0 na pilha de operandos.
}
// 0x0E
void dconst_0(MethodData *method_data)
{
    // Colocar a constante double 0.0 na pilha de operandos.
    // Usa 2 espacos na pilha.
}
// 0x0F
void dconst_1(MethodData *method_data)
{
    // Colocar a constante double 1.0 na pilha de operandos.
    // Usa 2 espacos na pilha.
}
// 0x10
void bipush(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    // Reimplement
    int *byte = (int *)malloc(sizeof(int));
    *byte = method_data->code.code[method_data->pc + 1];
    stack_push(current_frame->operand_stack, byte);
    method_data->pc += 1;
}
// 0x11
void sipush(MethodData *method_data)
{
}
// 0x12
void ldc(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);

    u2 index = method_data->code.code[method_data->pc + 1];
    stack_push(current_frame->operand_stack, current_frame->constant_pool + index - 1);
    method_data->pc += 1;
}
// 0x13
void ldc_w(MethodData *method_data)
{
}
// 0x14
void ldc2_w(MethodData *method_data)
{
}
// 0x15
void iload(MethodData *method_data)
{
}
// 0x16
void lload(MethodData *method_data)
{
}
// 0x17
void fload(MethodData *method_data)
{
}
// 0x18
void dload(MethodData *method_data)
{
}
// 0x19
void aload(MethodData *method_data)
{
}
// 0x1A
void iload_0(MethodData *method_data)
{
}
// 0x1B
void iload_1(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    stack_push(current_frame->operand_stack, current_frame->local_variables[1]);
}
// 0x1C
void iload_2(MethodData *method_data)
{
}
// 0x1D
void iload_3(MethodData *method_data)
{
}
// 0x1E
void lload_0(MethodData *method_data)
{
}
// 0x1F
void lload_1(MethodData *method_data)
{
}
// 0x20
void lload_2(MethodData *method_data)
{
}
// 0x21
void lload_3(MethodData *method_data)
{
}
// 0x22
void fload_0(MethodData *method_data)
{
}
// 0x23
void fload_1(MethodData *method_data)
{
}
// 0x24
void fload_2(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    cp_info *element = current_frame->local_variables[2];
    u4 fvalue = element->info.Float.bytes;

    float *float_value = (float *)malloc(sizeof(float));
    *float_value = ieee754_single(fvalue);

    stack_push(current_frame->operand_stack, float_value);
}
// 0x25
void fload_3(MethodData *method_data)
{
}
// 0x26
void dload_0(MethodData *method_data)
{
}
// 0x27
void dload_1(MethodData *method_data)
{
}
// 0x28
void dload_2(MethodData *method_data)
{
}
// 0x29
void dload_3(MethodData *method_data)
{
}
// 0x2A
void aload_0(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    void *value = current_frame->local_variables[0];
    stack_push(current_frame->operand_stack, value);
}
// 0x2B
void aload_1(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    stack_push(current_frame->operand_stack, current_frame->local_variables[1]);
}
// 0x2C
void aload_2(MethodData *method_data)
{
}
// 0x2D
void aload_3(MethodData *method_data)
{
}
// 0x2E
void iaload(MethodData *method_data)
{
}
// 0x2F
void laload(MethodData *method_data)
{
}
// 0x30
void faload(MethodData *method_data)
{
}
// 0x31
void daload(MethodData *method_data)
{
}
// 0x32
void aaload(MethodData *method_data)
{
}
// 0x33
void baload(MethodData *method_data)
{
}
// 0x34
void caload(MethodData *method_data)
{
}
// 0x35
void saload(MethodData *method_data)
{
}
// 0x36
void istore(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);

    u1 index_byte = method_data->code.code[method_data->pc + 1];
    int32_t value = *(int32_t *)stack_top(current_frame->operand_stack);

    stack_pop(current_frame->operand_stack);
    *((int32_t *)current_frame->local_variables[index_byte]) = value;

    method_data->pc += 1;
}
// 0x37
void lstore(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);

    u1 index_byte = method_data->code.code[method_data->pc + 1];
    u8 value = *(u8 *)stack_top(current_frame->operand_stack);

    stack_pop(current_frame->operand_stack);
    *((u8 *)current_frame->local_variables[index_byte]) = value;

    method_data->pc += 1;
}

// 0x38
void fstore(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);

    u1 index_byte = method_data->code.code[method_data->pc + 1];
    float value = *(float *)stack_top(current_frame->operand_stack);

    stack_pop(current_frame->operand_stack);
    *((float *)current_frame->local_variables[index_byte]) = value;

    method_data->pc += 1;
}
// 0x39
void dstore(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);

    u1 index_byte = method_data->code.code[method_data->pc + 1];
    double value = *(double *)stack_top(current_frame->operand_stack);

    stack_pop(current_frame->operand_stack);
    *((double *)current_frame->local_variables[index_byte]) = value;

    method_data->pc += 1;
}

// 0x3A
void astore(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);

    u1 index_byte = method_data->code.code[method_data->pc + 1];
    void *value = stack_top(current_frame->operand_stack);

    stack_pop(current_frame->operand_stack);
    current_frame->local_variables[index_byte] = value;

    method_data->pc += 1;
}

// 0x3B
void istore_0(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);

    int32_t value = *(int32_t *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    *((int32_t *)current_frame->local_variables[0]) = value;
}
// 0x3C
void istore_1(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    current_frame->local_variables[1] = stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);
}
// 0x3D
void istore_2(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);

    int32_t value = *(int32_t *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    *((int32_t *)current_frame->local_variables[2]) = value;
}
// 0x3E
void istore_3(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);

    int32_t value = *(int32_t *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    *((int32_t *)current_frame->local_variables[3]) = value;
}
// 0x3F
void lstore_0(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    u8 value = *((u8 *)stack_top(current_frame->operand_stack));
    stack_pop(current_frame->operand_stack);
    *((u8 *)(current_frame->local_variables[1])) = value;
}

// 0x40
void lstore_1(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    u8 value = *((u8 *)stack_top(current_frame->operand_stack));
    stack_pop(current_frame->operand_stack);
    *((u8 *)(current_frame->local_variables[1])) = value;
}
// 0x41
void lstore_2(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    u8 value = *((u8 *)stack_top(current_frame->operand_stack));
    stack_pop(current_frame->operand_stack);
    *((u8 *)(current_frame->local_variables[2])) = value;
}
// 0x42
void lstore_3(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    u8 value = *((u8 *)stack_top(current_frame->operand_stack));
    stack_pop(current_frame->operand_stack);
    *((u8 *)(current_frame->local_variables[3])) = value;
}
// 0x43
void fstore_0(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);

    float value = *(float *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    *((float *)current_frame->local_variables[0]) = value;
}
// 0x44
void fstore_1(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);

    float value = *(float *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    *((float *)current_frame->local_variables[1]) = value;
}
// 0x45
void fstore_2(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);

    current_frame->local_variables[2] = stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);
}
// 0x46
void fstore_3(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);

    float value = *(float *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    *((float *)current_frame->local_variables[3]) = value;
}
// 0x47
void dstore_0(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);

    double value = *(double *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    *((double *)current_frame->local_variables[0]) = value;
}

// 0x48
void dstore_1(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);

    double value = *(double *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    *((double *)current_frame->local_variables[1]) = value;
}

// 0x49
void dstore_2(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);

    double value = *(double *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    *((double *)current_frame->local_variables[2]) = value;
}

// 0x4A
void dstore_3(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);

    double value = *(double *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    *((double *)current_frame->local_variables[3]) = value;
}

// 0x4B
void astore_0(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);

    void *value = (void *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[0] = value;
}
// 0x4C
void astore_1(MethodData *method_data)
{
    // Armazena uma referência na segunda posição das variáveis locais.
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);

    void *value = (void *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[1] = value;
}
// 0x4D
void astore_2(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);

    void *value = (void *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[2] = value;
}
// 0x4E
void astore_3(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);

    void *value = (void *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[3] = value;
}
// 0x4F
void iastore(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);

    int value = *(int *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    int index = *(int *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    int *array_ref = (int *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    array_ref[index] = value;
}

// 0x50
void lastore(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);

    u8 value = *(u8 *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    int index = *(int *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    u8 *array_ref = (u8 *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    array_ref[index] = value;
}

// 0x51
void fastore(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);

    float value = *(float *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    int index = *(int *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    float *array_ref = (float *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    array_ref[index] = value;
}

// 0x52
void dastore(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);

    double value = *(double *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    int index = *(int *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    double *array_ref = (double *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    array_ref[index] = value;
}

// 0x53
void aastore(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);

    void *value = stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    int index = *(int *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    void **array_ref = (void **)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    array_ref[index] = value;
}

// 0x54
void bastore(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);

    char value = *(char *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    int index = *(int *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    char *array_ref = (char *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    array_ref[index] = value;
}

// 0x55
void castore(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);

    char value = *(char *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    int index = *(int *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    char *array_ref = (char *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    array_ref[index] = value;
}

// 0x56
void sastore(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);

    short value = *(short *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    int index = *(int *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    short *array_ref = (short *)stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    array_ref[index] = value;
}

// 0x57 (optional implementation?MethodData* method_data)
void pop(MethodData *method_data)
{
}
// 0x58 (optional implementation?MethodData* method_data)
void pop2(MethodData *method_data)
{
}
// 0x59 (optional implementation?MethodData* method_data)
void dup(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    Node *top = stack_top(current_frame->operand_stack);
    stack_push(current_frame->operand_stack, top);
}
// 0x5A (optional implementation?MethodData* method_data)
void dup_x1(MethodData *method_data)
{
}
// 0x5B (optional implementation?MethodData* method_data)
void dup_x2(MethodData *method_data)
{
}
// 0x5C (optional implementation?MethodData* method_data)
void dup2(MethodData *method_data)
{
}
// 0x5D (optional implementation?MethodData* method_data)
void dup2_x1(MethodData *method_data)
{
}
// 0x5E (optional implementation?MethodData* method_data)
void dup2_x2(MethodData *method_data)
{
}
// 0x5F (optional implementation?MethodData* method_data)
void swap(MethodData *method_data)
{
}
// 0x60
void iadd(MethodData *method_data)
{
}
// 0x61
void ladd(MethodData *method_data)
{
}
// 0x62
void fadd(MethodData *method_data)
{
}
// 0x63
void dadd(MethodData *method_data)
{
}
// 0x64
void isub(MethodData *method_data)
{
}
// 0x65
void lsub(MethodData *method_data)
{
}
// 0x66
void fsub(MethodData *method_data)
{
}
// 0x67
void dsub(MethodData *method_data)
{
}
// 0x68
void imul(MethodData *method_data)
{
}
// 0x69
void lmul(MethodData *method_data)
{
}
// 0x6A
void fmul(MethodData *method_data)
{
}
// 0x6B
void dmul(MethodData *method_data)
{
}
// 0x6C
void idiv(MethodData *method_data)
{
}
// 0x6D
void ldiv(MethodData *method_data)
{
}
// 0x6E
void fdiv(MethodData *method_data)
{
}
// 0x6F
void ddiv(MethodData *method_data)
{
}
// 0x70
void irem(MethodData *method_data)
{
}
// 0x71
void lrem(MethodData *method_data)
{
}
// 0x72
void frem(MethodData *method_data)
{
}
// 0x73
void drem(MethodData *method_data)
{
}
// 0x74
void ineg(MethodData *method_data)
{
}
// 0x75
void lneg(MethodData *method_data)
{
}
// 0x76
void fneg(MethodData *method_data)
{
}
// 0x77
void dneg(MethodData *method_data)
{
}
// 0x78
void ishl(MethodData *method_data)
{
}
// 0x79
void lshl(MethodData *method_data)
{
}
// 0x7A
void ishr(MethodData *method_data)
{
}
// 0x7B
void lshr(MethodData *method_data)
{
}
// 0x7C
void iushr(MethodData *method_data)
{
}
// 0x7D
void lushr(MethodData *method_data)
{
}
// 0x7E
void iand(MethodData *method_data)
{
}
// 0x7F
void land(MethodData *method_data)
{
}
// 0x80
void ior(MethodData *method_data)
{
}
// 0x81
void lor(MethodData *method_data)
{
}
// 0x82
void ixor(MethodData *method_data)
{
}
// 0x83
void lxor(MethodData *method_data)
{
}
// 0x84
void iinc(MethodData *method_data)
{
}
// 0x85
void i2l(MethodData *method_data)
{
}
// 0x86
void i2f(MethodData *method_data)
{
}
// 0x87
void i2d(MethodData *method_data)
{
}
// 0x88
void l2i(MethodData *method_data)
{
}
// 0x89
void l2f(MethodData *method_data)
{
}
// 0x8A
void l2d(MethodData *method_data)
{
}
// 0x8B
void f2i(MethodData *method_data)
{
}
// 0x8C
void f2l(MethodData *method_data)
{
}
// 0x8D
void f2d(MethodData *method_data)
{
}
// 0x8E
void d2i(MethodData *method_data)
{
}
// 0x8F
void d2l(MethodData *method_data)
{
}
// 0x90
void d2f(MethodData *method_data)
{
}
// 0x91
void i2b(MethodData *method_data)
{
}
// 0x92
void i2c(MethodData *method_data)
{
}
// 0x93
void i2s(MethodData *method_data)
{
}
// 0x94
void lcmp(MethodData *method_data)
{
}
// 0x95
void fcmpl(MethodData *method_data)
{
}
// 0x96
void fcmpg(MethodData *method_data)
{
}
// 0x97
void dcmpl(MethodData *method_data)
{
}
// 0x98
void dcmpg(MethodData *method_data)
{
}
// 0x99
void ifeq(MethodData *method_data)
{
}
// 0x9A
void ifne(MethodData *method_data)
{
}
// 0x9B
void iflt(MethodData *method_data)
{
}
// 0x9C
void ifge(MethodData *method_data)
{
}
// 0x9D
void ifgt(MethodData *method_data)
{
}
// 0x9E
void ifle(MethodData *method_data)
{
}
// 0x9F
void if_icmpeq(MethodData *method_data)
{
}
// 0xA0
void if_icmpne(MethodData *method_data)
{
}
// 0xA1
void if_icmplt(MethodData *method_data)
{
}
// 0xA2
void if_icmpge(MethodData *method_data)
{
}
// 0xA3
void if_icmpgt(MethodData *method_data)
{
}
// 0xA4
void if_icmple(MethodData *method_data)
{
}
// 0xA5
void if_acmpeg(MethodData *method_data)
{
}
// 0xA6
void if_acmpne(MethodData *method_data)
{
}
// 0xA7 ("goto" is a C keyword, hence the nameMethodData* method_data)
void jvm_goto(MethodData *method_data)
{
}
// 0xA8
void jsr(MethodData *method_data)
{
}
// 0xA9
void ret(MethodData *method_data)
{
}
// 0xAA
void tableswitch(MethodData *method_data)
{
}
// 0xAB
void lookupswitch(MethodData *method_data)
{
}
// 0xAC
void ireturn(MethodData *method_data)
{
}
// 0xAD
void lreturn(MethodData *method_data)
{
}
// 0xAE
void freturn(MethodData *method_data)
{
}
// 0xAF
void dreturn(MethodData *method_data)
{
}
// 0xB0
void areturn(MethodData *method_data)
{
}
// 0xB1 ("return" is a C keyword, hence the nameMethodData* method_data)
void jvm_return(MethodData *method_data)
{
}
// 0xB2
void getstatic(MethodData *method_data)
{
    u2 index_byte1 = method_data->code.code[method_data->pc + 1];
    u2 index_byte2 = method_data->code.code[method_data->pc + 2];
    u2 index = (index_byte1 << 8) | index_byte2;

    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);

    u2 class_index = current_frame->constant_pool[index - 1].info.Fieldref.class_index;

    char class_name[300];
    get_class_name(class_index, current_frame->constant_pool, class_name);

    u2 name_type_index = current_frame->constant_pool[index - 1].info.Fieldref.name_and_type_index;
    u2 descriptor_index = current_frame->constant_pool[name_type_index - 1].info.NameAndType.descriptor_index;
    char descriptor_content[300];
    get_utf8_value(descriptor_index - 1, current_frame->constant_pool, descriptor_content);

    if (!strcmp(class_name, "java/lang/System"))
    {
        // Need to be implemented
    }

    method_data->pc += 2;
}
// 0xB3
void putstatic(MethodData *method_data)
{
}
// 0xB4
void getfield(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    JVMObject *object = stack_top(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);

    u2 index_byte1 = method_data->code.code[method_data->pc + 1];
    u2 index_byte2 = method_data->code.code[method_data->pc + 2];
    u2 index = (index_byte1 << 8) | index_byte2;

    u2 field_name_type_index = object->class->constant_pool[index - 1].info.Fieldref.name_and_type_index;
    u2 field_name_index = object->class->constant_pool[field_name_type_index - 1].info.NameAndType.name_index;

    CONSTANT_Utf8_info field_name = object->class->constant_pool[field_name_index - 1].info.Utf8;
    u2 field_name_size = field_name.length;
    char field_get[field_name_size + 1];
    get_utf8_value(field_name_index - 1, object->class->constant_pool, field_get);

    for (u2 element = 0; element < object->class->fields_count; element++)
    {
        field_name_index = object->data[element].field->name_index;
        field_name = object->class->constant_pool[field_name_index - 1].info.Utf8;
        field_name_size = field_name.length;
        char current_field[field_name_size];
        get_utf8_value(field_name_index - 1, object->class->constant_pool, current_field);

        if (!strcmp(current_field, field_get))
        {
            void *value = object->data[element].value;
            stack_push(current_frame->operand_stack, value);
        }
    }

    method_data->pc += 2;
}
// 0xB5
void putfield(MethodData *method_data)
{
    u2 index_byte1 = method_data->code.code[method_data->pc + 1];
    u2 index_byte2 = method_data->code.code[method_data->pc + 2];
    u2 index = (index_byte1 << 8) | index_byte2;

    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);

    ClassFile *object_class = method_data->object->class;
    u2 field_name_type_index = object_class->constant_pool[index - 1].info.Fieldref.name_and_type_index;
    u2 field_name_index = object_class->constant_pool[field_name_type_index - 1].info.NameAndType.name_index;

    CONSTANT_Utf8_info field_name = object_class->constant_pool[field_name_index - 1].info.Utf8;
    u2 field_name_size = field_name.length;
    char field_put[field_name_size + 1];
    get_utf8_value(field_name_index - 1, object_class->constant_pool, field_put);

    for (u2 element = 0; element < object_class->fields_count; element++)
    {
        field_name_index = method_data->object->data[element].field->name_index;
        field_name = object_class->constant_pool[field_name_index - 1].info.Utf8;
        field_name_size = field_name.length;
        char current_field[field_name_size];
        get_utf8_value(field_name_index - 1, object_class->constant_pool, current_field);
        if (!strcmp(current_field, field_put))
        {
            method_data->object->data[element].value = stack_top(current_frame->operand_stack);
            stack_pop(current_frame->operand_stack);
            break;
        }
    }

    method_data->pc += 2;
}
// 0xB6
void invokevirtual(MethodData *method_data)
{
    u2 index_byte1 = method_data->code.code[method_data->pc + 1];
    u2 index_byte2 = method_data->code.code[method_data->pc + 2];
    u2 index = (index_byte1 << 8) | index_byte2;

    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);

    CONSTANT_Fieldref_info field = current_frame->constant_pool[index - 1].info.Fieldref;
    char class_name[400];
    get_class_name(field.class_index, current_frame->constant_pool, class_name);

    if (!strcmp(class_name, "java/io/PrintStream"))
    {
        u2 descriptor_index =
            current_frame->constant_pool[field.name_and_type_index - 1].info.NameAndType.descriptor_index;
        char descriptor[400];
        get_utf8_value(descriptor_index - 1, current_frame->constant_pool, descriptor);

        if (!strcmp(descriptor, "(Ljava/lang/String;)V"))
        {
            cp_info *element = (cp_info *)stack_top(current_frame->operand_stack);
            switch (element->tag)
            {
            case CONSTANT_String: {
                u2 index = element->info.String.string_index - 1;
                element = (cp_info *)(&current_frame->constant_pool[index]);
            }
            case CONSTANT_Utf8: {
                u2 size = element->info.Utf8.length;
                char string[size + 1];
                for (u2 string_index = 0; string_index < size; ++string_index)
                {
                    string[string_index] = element->info.Utf8.bytes[string_index];
                }
                string[size] = '\0';
                printf("%s\n", string);
            }
            }
            u2 index = element->info.String.string_index - 1;
            element = (cp_info *)(&current_frame->constant_pool[index]);
        }
        else if (!strcmp(descriptor, "(I)V") || !strcmp(descriptor, "(B)V") || !strcmp(descriptor, "(Z)V") ||
                 !strcmp(descriptor, "(S)V"))
        {
            int *value = stack_top(current_frame->operand_stack);
            printf("%d\n", *value);
        }
        else if (!strcmp(descriptor, "(F)V"))
        {
            float *value = stack_top(current_frame->operand_stack);
            printf("%f\n", *value);
        }
        else if (!strcmp(descriptor, "(J)V"))
        {
            long long int *value = stack_top(current_frame->operand_stack);
            printf("%lld\n", *value);
        }
        else if (!strcmp(descriptor, "(D)V"))
        {
            double *value = stack_top(current_frame->operand_stack);
            printf("%lf\n", *value);
        }
        else if (!strcmp(descriptor, "(C)V"))
        {
            char *value = stack_top(current_frame->operand_stack);
            printf("%c\n", *value);
        }

        if (strcmp(descriptor, "(Ljava/lang/String;)V"))
        {
            free(stack_top(current_frame->operand_stack));
        }
        stack_pop(current_frame->operand_stack);
    }

    method_data->pc += 2;
}
// 0xB7
void invokespecial(MethodData *method_data)
{
    u2 index_byte1 = method_data->code.code[method_data->pc + 1];
    u2 index_byte2 = method_data->code.code[method_data->pc + 2];
    u2 index = (index_byte1 << 8) | index_byte2;

    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);

    CONSTANT_Methodref_info method = current_frame->constant_pool[index - 1].info.Methodref;
    u2 class_index = method.class_index;
    char class_name[400];
    get_class_name(class_index, current_frame->constant_pool, class_name);

    if (!strcmp(class_name, "java/lang/Object"))
    {
    }
    else
    {
        u2 name_type_index = method.name_and_type_index;
        u2 method_name_index = current_frame->constant_pool[name_type_index - 1].info.NameAndType.name_index;
        u2 method_name_desc_index = current_frame->constant_pool[name_type_index - 1].info.NameAndType.descriptor_index;

        u2 method_name_size = current_frame->constant_pool[method_name_index - 1].info.Utf8.length;
        char name[method_name_size + 1];
        get_utf8_value(method_name_index - 1, current_frame->constant_pool, name);

        u2 method_desc_size = current_frame->constant_pool[method_name_desc_index - 1].info.Utf8.length;
        char descriptor[method_desc_size + 1];
        get_utf8_value(method_name_desc_index - 1, current_frame->constant_pool, descriptor);

        ClassFile *current_class = class_file_list_get(method_data->loaded_classes, class_name);
        method_info *current_method = method_area_search_method(name, current_class);
        u2 object_stack_position = current_method->attributes->info.code.max_locals;

        Node *node_pos = current_frame->operand_stack->top;
        for (u2 pop = 0; pop < object_stack_position - 1; ++pop)
        {
            node_pos = node_pos->next;
        }

        jvm_debug_print("[Changing to class %s]\n", class_name);

        JVMObject *object = node_pos->data;
        method_area_call_method(current_method, current_class->constant_pool, method_data->frame_stack,
                                method_data->loaded_classes, object);
        jvm_debug_print("[Exiting from class %s]\n\n", class_name);
    }

    method_data->pc += 2;
}
// 0xB8
void invokestatic(MethodData *method_data)
{
    u2 index_byte1 = method_data->code.code[method_data->pc + 1];
    u2 index_byte2 = method_data->code.code[method_data->pc + 2];
    u2 index = (index_byte1 << 8) | index_byte2;

    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);

    CONSTANT_Methodref_info method = current_frame->constant_pool[index - 1].info.Methodref;
    u2 class_index = method.class_index;
    char class_name[400];
    get_class_name(class_index, current_frame->constant_pool, class_name);

    if (!strcmp(class_name, "java/lang/Object"))
    {
    }
    else
    {
        u2 name_type_index = method.name_and_type_index;
        u2 method_name_index = current_frame->constant_pool[name_type_index - 1].info.NameAndType.name_index;
        u2 method_name_desc_index = current_frame->constant_pool[name_type_index - 1].info.NameAndType.descriptor_index;

        u2 method_name_size = current_frame->constant_pool[method_name_index - 1].info.Utf8.length;
        char name[method_name_size + 1];
        get_utf8_value(method_name_index - 1, current_frame->constant_pool, name);

        u2 method_desc_size = current_frame->constant_pool[method_name_desc_index - 1].info.Utf8.length;
        char descriptor[method_desc_size + 1];
        get_utf8_value(method_name_desc_index - 1, current_frame->constant_pool, descriptor);

        ClassFile *current_class = class_file_list_get(method_data->loaded_classes, class_name);
        method_info *current_method = method_area_search_method(name, current_class);

        jvm_debug_print("[Changing to class %s]", class_name);
        method_area_call_method(current_method, current_class->constant_pool, method_data->frame_stack,
                                method_data->loaded_classes, NULL);
    }

    method_data->pc += 2;
}
// 0xB9
void invokeinterface(MethodData *method_data)
{
}
// 0xBB (skipped 0xBA (186MethodData* method_data) - invokedynamicMethodData* method_data)
void new_func(MethodData *method_data)
{
    u2 index_byte1 = method_data->code.code[method_data->pc + 1];
    u2 index_byte2 = method_data->code.code[method_data->pc + 2];
    u2 index = (index_byte1 << 8) | index_byte2;

    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);

    char class_name[400];
    get_class_name(index, current_frame->constant_pool, class_name);

    u2 class_path_size =
        strlen(current_frame->constant_pool[index - 1].info.Class.path) + strlen(class_name) + strlen(".class");
    char path[class_path_size];
    strcpy(path, current_frame->constant_pool[index - 1].info.Class.path);
    strcat(path, class_name);
    strcat(path, ".class");

    ClassFile *new_class = (ClassFile *)malloc(sizeof(ClassFile));
    *new_class = load_class_file(path);
    class_file_list_insert(method_data->loaded_classes, new_class, class_name);

    JVMObject *new_object = object_init_dynamic(new_class);
    stack_push(current_frame->operand_stack, new_object);

    method_data->pc += 2;
}
// 0xBC
void newarray(MethodData *method_data)
{
}
// 0xBD
void anewarray(MethodData *method_data)
{
}
// 0xBE
void arraylength(MethodData *method_data)
{
}
// 0xBF (optional implementation?MethodData* method_data)
void athrow(MethodData *method_data)
{
}
// 0xC0 (optional implementation?MethodData* method_data)
void checkcast(MethodData *method_data)
{
}
// 0xC1 (optional implementation?MethodData* method_data)
void instanceof (MethodData * method_data)
{
}
// 0xC2 (optional implementation?MethodData* method_data)
void monitorenter(MethodData *method_data)
{
}
// 0xC3 (optional implementation?MethodData* method_data)
void monitorexit(MethodData *method_data)
{
}
// 0xC4
void wide(MethodData *method_data)
{
}
// 0xC5
void multianewarray(MethodData *method_data)
{
}
// 0xC6
void ifnull(MethodData *method_data)
{
}
// 0xC7
void ifnonnull(MethodData *method_data)
{
}
// 0xC8
void goto_w(MethodData *method_data)
{
}
// 0xC9
void jsr_w(MethodData *method_data)
{
}