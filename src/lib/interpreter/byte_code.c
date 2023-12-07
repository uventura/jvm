#include "lib/interpreter/byte_code.h"
#include "lib/base/class_file/cp_info.h"
#include "lib/base/structures/stack.h"
#include "lib/runtime_data_area/frame.h"
#include "lib/runtime_data_area/method_area.h"

#include <string.h>

// Functions for the opcode.

// 0x00
void nop(MethodData *method_data)
{
    // Não realiza nenhuma operação.
}

// 0x01
void aconst_null(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    stack_push(current_frame->operand_stack, NULL);
}

// 0x02
void iconst_m1(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    int *value = (int *)malloc(sizeof(int));
    *value = -1;
    stack_push(current_frame->operand_stack, value);
}

// 0x03
void iconst_0(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    int *value = (int *)malloc(sizeof(int));
    *value = 0;
    stack_push(current_frame->operand_stack, value);
}

// 0x04
void iconst_1(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    int *value = (int *)malloc(sizeof(int));
    *value = 1;
    stack_push(current_frame->operand_stack, value);
}

// 0x05
void iconst_2(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    int *value = (int *)malloc(sizeof(int));
    *value = 2;
    stack_push(current_frame->operand_stack, value);
}

// 0x06
void iconst_3(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    int *value = (int *)malloc(sizeof(int));
    *value = 3;
    stack_push(current_frame->operand_stack, value);
}

// 0x07
void iconst_4(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    int *value = (int *)malloc(sizeof(int));
    *value = 4;
    stack_push(current_frame->operand_stack, value);
}

// 0x08
void iconst_5(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    int *value = (int *)malloc(sizeof(int));
    *value = 5;
    stack_push(current_frame->operand_stack, value);
}

// 0x09
void lconst_0(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    long *value = (long *)malloc(sizeof(long));
    *value = 0;
    stack_push(current_frame->operand_stack, value);
}
// 0x0A
void lconst_1(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    long *value = (long *)malloc(sizeof(long));
    *value = 1;
    stack_push(current_frame->operand_stack, value);
}

// 0x0B
void fconst_0(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    float *value = (float *)malloc(sizeof(float));
    *value = 0.0f;
    stack_push(current_frame->operand_stack, value);
}

// 0x0C
void fconst_1(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    float *value = (float *)malloc(sizeof(float));
    *value = 1.0f;
    stack_push(current_frame->operand_stack, value);
}

// 0x0D
void fconst_2(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    float *value = (float *)malloc(sizeof(float));
    *value = 2.0f;
    stack_push(current_frame->operand_stack, value);
}

// 0x0E
void dconst_0(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    double *value = (double *)malloc(sizeof(double));
    *value = 0.0;
    stack_push(current_frame->operand_stack, value);
}

// 0x0F
void dconst_1(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    double *value = (double *)malloc(sizeof(double));
    *value = 1.0;
    stack_push(current_frame->operand_stack, value);
}

// 0x10
void bipush(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    int *value = (int *)malloc(sizeof(int));
    *value = (int)method_data->code.code[method_data->pc + 1];
    stack_push(current_frame->operand_stack, value);
    method_data->pc += 1;
}

// 0x11
void sipush(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    int *value = (int *)malloc(sizeof(int));
    u2 byte1 = method_data->code.code[method_data->pc + 1];
    u2 byte2 = method_data->code.code[method_data->pc + 2];
    *value = (int)((byte1 << 8) | byte2);
    stack_push(current_frame->operand_stack, value);
    method_data->pc += 2;
}
// 0x12
void ldc(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    u2 index = method_data->code.code[method_data->pc + 1];
    cp_info element = current_frame->constant_pool[index - 1];

    if (element.tag == CONSTANT_String)
    {
        u2 utf8_index = current_frame->constant_pool[index - 1].info.String.string_index;
        char *string = get_utf8_string(utf8_index, current_frame->constant_pool);
        stack_push(current_frame->operand_stack, string);
    }

    method_data->pc += 2;
}

// 0x13
void ldc_w(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    u2 index = read_u2(&method_data->code.code[method_data->pc + 1]);
    cp_info element = current_frame->constant_pool[index - 1];

    if (element.tag == CONSTANT_String)
    {
        u2 utf8_index = current_frame->constant_pool[index - 1].info.String.string_index;
        char *string = get_utf8_string(utf8_index, current_frame->constant_pool);
        stack_push(current_frame->operand_stack, string);
    }

    method_data->pc += 3;
}

// 0x14
void ldc2_w(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    u2 index = read_u2(&method_data->code.code[method_data->pc + 1]);
    cp_info element = current_frame->constant_pool[index - 1];

    if (element.tag == CONSTANT_Long)
    {
        CONSTANT_Long_info long_element = element.info.Long;
        long long_value = ((long)long_element.high_bytes << 32) | long_element.low_bytes;
        // Empilhar long_value na pilha de operandos
    }
    else if (element.tag == CONSTANT_Double)
    {
        CONSTANT_Double_info double_element = element.info.Double;
        double double_value;
        // Converte os bytes para um valor double e empilha na pilha de operandos
    }

    method_data->pc += 3;
}


// 0x15
void iload(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    u1 index = method_data->code.code[method_data->pc + 1];
    int *value = (int *)(current_frame->local_variables[index]);
    stack_push(current_frame->operand_stack, value);
    method_data->pc += 2;
}

// 0x16
void lload(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    u1 index = method_data->code.code[method_data->pc + 1];
    long *value = (long *)(current_frame->local_variables[index]);
    stack_push(current_frame->operand_stack, value);
    method_data->pc += 2;
}

// 0x17
void fload(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    u1 index = method_data->code.code[method_data->pc + 1];
    float *value = (float *)(current_frame->local_variables[index]);
    stack_push(current_frame->operand_stack, value);
    method_data->pc += 2;
}

// 0x18
void dload(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    u1 index = method_data->code.code[method_data->pc + 1];
    double *value = (double *)(current_frame->local_variables[index]);
    stack_push(current_frame->operand_stack, value);
    method_data->pc += 2;
}

// 0x19
void aload(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    u1 index = method_data->code.code[method_data->pc + 1];
    void *ref = current_frame->local_variables[index];
    stack_push(current_frame->operand_stack, ref);
    method_data->pc += 2;
}

// 0x1A
void iload_0(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    int *value = (int *)(current_frame->local_variables[0]);
    stack_push(current_frame->operand_stack, value);
}

// 0x1B
void iload_1(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    int *value = (int *)(current_frame->local_variables[1]);
    stack_push(current_frame->operand_stack, value);
}


// 0x1C
void iload_2(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    int *value = (int *)(current_frame->local_variables[2]);
    stack_push(current_frame->operand_stack, value);
}

// 0x1D
void iload_3(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    int *value = (int *)(current_frame->local_variables[3]);
    stack_push(current_frame->operand_stack, value);
}

// 0x1E
void lload_0(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    long *value = (long *)(current_frame->local_variables[0]);
    stack_push(current_frame->operand_stack, value);
}

// 0x1F
void lload_1(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    long *value = (long *)(current_frame->local_variables[1]);
    stack_push(current_frame->operand_stack, value);
}

// 0x20
void lload_2(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    long *value = (long *)(current_frame->local_variables[2]);
    stack_push(current_frame->operand_stack, value);
}

// 0x21
void lload_3(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    long *value = (long *)(current_frame->local_variables[3]);
    stack_push(current_frame->operand_stack, value);
}

// 0x22
void fload_0(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    float *value = (float *)(current_frame->local_variables[0]);
    stack_push(current_frame->operand_stack, value);
}

// 0x23
void fload_1(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    float *value = (float *)(current_frame->local_variables[1]);
    stack_push(current_frame->operand_stack, value);
}

// 0x24
void fload_2(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    float *value = (float *)(current_frame->local_variables[2]);
    stack_push(current_frame->operand_stack, value);
}

// 0x25
void fload_3(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    float *value = (float *)(current_frame->local_variables[3]);
    stack_push(current_frame->operand_stack, value);
}

// 0x26
void dload_0(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    double *value = (double *)(current_frame->local_variables[0]);
    stack_push(current_frame->operand_stack, value);
}

// 0x27
void dload_1(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    double *value = (double *)(current_frame->local_variables[1]);
    stack_push(current_frame->operand_stack, value);
}

// 0x28
void dload_2(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    double *value = (double *)(current_frame->local_variables[2]);
    stack_push(current_frame->operand_stack, value);
}

// 0x29
void dload_3(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    double *value = (double *)(current_frame->local_variables[3]);
    stack_push(current_frame->operand_stack, value);
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
    void *value = current_frame->local_variables[1];
    stack_push(current_frame->operand_stack, value);
}

// 0x2C
void aload_2(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    void *value = current_frame->local_variables[2];
    stack_push(current_frame->operand_stack, value);
}

// 0x2D
void aload_3(MethodData *method_data)
{
    Frame *current_frame = stack_top(method_data->frame_stack);
    void *value = current_frame->local_variables[3];
    stack_push(current_frame->operand_stack, value);
}

// Carrega um inteiro de um array especificado pelo índice e pela referência do array na pilha de operandos.
void iaload(MethodData *method_data) {
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int index = *((int *)stack_pop(current_frame->operand_stack));
    int *array_ref = (int *)stack_pop(current_frame->operand_stack);
    int value = array_ref[index];
    stack_push(current_frame->operand_stack, &value);
}

// 0x2F
// Carrega um long de um array especificado pelo índice e pela referência do array na pilha de operandos.
void laload(MethodData *method_data) {
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int index = *((int *)stack_pop(current_frame->operand_stack));
    long *array_ref = (long *)stack_pop(current_frame->operand_stack);
    long value = array_ref[index];
    stack_push(current_frame->operand_stack, &value);
}

// 0x30
// Carrega um float de um array especificado pelo índice e pela referência do array na pilha de operandos.
void faload(MethodData *method_data) {
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int index = *((int *)stack_pop(current_frame->operand_stack));
    float *array_ref = (float *)stack_pop(current_frame->operand_stack);
    float value = array_ref[index];
    stack_push(current_frame->operand_stack, &value);
}

// 0x31
// Carrega um double de um array especificado pelo índice e pela referência do array na pilha de operandos.
void daload(MethodData *method_data) {
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int index = *((int *)stack_pop(current_frame->operand_stack));
    double *array_ref = (double *)stack_pop(current_frame->operand_stack);
    double value = array_ref[index];
    stack_push(current_frame->operand_stack, &value);
}

// 0x32
// Carrega uma referência de um array de referências especificado pelo índice e pela referência do array na pilha de operandos.
void aaload(MethodData *method_data) {
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int index = *((int *)stack_pop(current_frame->operand_stack));
    void **array_ref = (void **)stack_pop(current_frame->operand_stack);
    void *value = array_ref[index];
    stack_push(current_frame->operand_stack, &value);
}

// 0x33
// Carrega um byte ou boolean de um array especificado pelo índice e pela referência do array na pilha de operandos.
void baload(MethodData *method_data) {
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int index = *((int *)stack_pop(current_frame->operand_stack));
    char *array_ref = (char *)stack_pop(current_frame->operand_stack);
    char value = array_ref[index];
    stack_push(current_frame->operand_stack, &value);
}

// 0x34
// Carrega um char de um array especificado pelo índice e pela referência do array na pilha de operandos.
void caload(MethodData *method_data) {
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int index = *((int *)stack_pop(current_frame->operand_stack));
    char *array_ref = (char *)stack_pop(current_frame->operand_stack);
    char value = array_ref[index];
    stack_push(current_frame->operand_stack, &value);
}

// 0x35
// Carrega um short de um array especificado pelo índice e pela referência do array na pilha de operandos.
void saload(MethodData *method_data) {
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int index = *((int *)stack_pop(current_frame->operand_stack));
    short *array_ref = (short *)stack_pop(current_frame->operand_stack);
    short value = array_ref[index];
    stack_push(current_frame->operand_stack, &value);
}

// 0x36
// Armazena um int de uma variável local ou da stack de operandos em um array.
void istore(MethodData *method_data) {
    int index = *((int *)stack_pop(method_data->frame_stack));
    int value = *((int *)stack_pop(method_data->frame_stack));
    method_data->local_variables[index] = value;
}

// 0x37
// Armazena um long de uma variável local ou da stack de operandos em um array.
void lstore(MethodData *method_data) {
    int index = *((int *)stack_pop(method_data->frame_stack));
    long value = *((long *)stack_pop(method_data->frame_stack));
    method_data->local_variables[index] = value;
}

// 0x38
// Armazena um float de uma variável local ou da stack de operandos em um array.
void fstore(MethodData *method_data) {
    int index = *((int *)stack_pop(method_data->frame_stack));
    float value = *((float *)stack_pop(method_data->frame_stack));
    method_data->local_variables[index] = value;
}

// 0x39
// Armazena um double de uma variável local ou da stack de operandos em um array.
void dstore(MethodData *method_data) {
    int index = *((int *)stack_pop(method_data->frame_stack));
    double value = *((double *)stack_pop(method_data->frame_stack));
    method_data->local_variables[index] = value;
}

// 0x3A
// Armazena uma referência de uma variável local ou da stack de operandos em um array.
void astore(MethodData *method_data) {
    int index = *((int *)stack_pop(method_data->frame_stack));
    void *value = stack_pop(method_data->frame_stack);
    method_data->local_variables[index] = value;
}

// 0x3B
// Armazena um int na primeira posição das variáveis locais.
void istore_0(MethodData *method_data) {
    int value = *((int *)stack_pop(method_data->frame_stack));
    method_data->local_variables[0] = value;
}

// 0x3C
// Armazena um int na segunda posição das variáveis locais.
void istore_1(MethodData *method_data) {
    int value = *((int *)stack_pop(method_data->frame_stack));
    method_data->local_variables[1] = value;
}

// 0x3D
// Armazena um int na terceira posição das variáveis locais.
void istore_2(MethodData *method_data) {
    int value = *((int *)stack_pop(method_data->frame_stack));
    method_data->local_variables[2] = value;
}

// 0x3E
// Armazena um int na quarta posição das variáveis locais.
void istore_3(MethodData *method_data) {
    int value = *((int *)stack_pop(method_data->frame_stack));
    method_data->local_variables[3] = value;
}

// 0x3F
// Armazena um long na primeira posição das variáveis locais.
void lstore_0(MethodData *method_data) {
    long value = *((long *)stack_pop(method_data->frame_stack));
    method_data->local_variables[0] = value;
}

// 0x40
// Armazena um long na segunda posição das variáveis locais.
void lstore_1(MethodData *method_data) {
    long value = *((long *)stack_pop(method_data->frame_stack));
    method_data->local_variables[1] = value;
}

// 0x41
// Armazena um long na terceira posição das variáveis locais.
void lstore_2(MethodData *method_data) {
    long value = *((long *)stack_pop(method_data->frame_stack));
    method_data->local_variables[2] = value;
}

// 0x42
// Armazena um long na quarta posição das variáveis locais.
void lstore_3(MethodData *method_data) {
    long value = *((long *)stack_pop(method_data->frame_stack));
    method_data->local_variables[3] = value;
}

// 0x43
// Armazena um float na primeira posição das variáveis locais.
void fstore_0(MethodData *method_data) {
    float value = *((float *)stack_pop(method_data->frame_stack));
    method_data->local_variables[0] = value;
}

// 0x44
// Armazena um float na segunda posição das variáveis locais.
void fstore_1(MethodData *method_data) {
    float value = *((float *)stack_pop(method_data->frame_stack));
    method_data->local_variables[1] = value;
}

// 0x45
// Armazena um float na terceira posição das variáveis locais.
void fstore_2(MethodData *method_data) {
    float value = *((float *)stack_pop(method_data->frame_stack));
    method_data->local_variables[2] = value;
}

// 0x46
// Armazena um float na quarta posição das variáveis locais.
void fstore_3(MethodData *method_data) {
    float value = *((float *)stack_pop(method_data->frame_stack));
    method_data->local_variables[3] = value;
}

// 0x47
// Armazena um double na primeira posição das variáveis locais.
void dstore_0(MethodData *method_data) {
    double value = *((double *)stack_pop(method_data->frame_stack));
    method_data->local_variables[0] = value;
}

// 0x48
// Armazena um double na segunda posição das variáveis locais.
void dstore_1(MethodData *method_data) {
    double value = *((double *)stack_pop(method_data->frame_stack));
    method_data->local_variables[1] = value;
}

// 0x49
// Armazena um double na terceira posição das variáveis locais.
void dstore_2(MethodData *method_data) {
    double value = *((double *)stack_pop(method_data->frame_stack));
    method_data->local_variables[2] = value;
}

// 0x4A
// Armazena um double na quarta posição das variáveis locais.
void dstore_3(MethodData *method_data) {
    double value = *((double *)stack_pop(method_data->frame_stack));
    method_data->

// 0x4B
// Armazena uma referência na primeira posição das variáveis locais.
void astore_0(MethodData *method_data) {
    void *value = stack_pop(method_data->frame_stack);
    method_data->local_variables[0] =

// 0x4C
// Armazena uma referência na segunda posição das variáveis locais.
void astore_1(MethodData *method_data) {
    void *value = stack_pop(method_data->frame_stack);
    method_data->local_variables[1] = value;
}

// 0x4D
// Armazena uma referência na terceira posição das variáveis locais.
void astore_2(MethodData *method_data) {
    void *value = stack_pop(method_data->frame_stack);
    method_data->local_variables[2] = value;
}

// 0x4E
// Armazena uma referência na quarta posição das variáveis locais.
void astore_3(MethodData *method_data) {
    void *value = stack_pop(method_data->frame_stack);
    method_data->local_variables[3] = value;
}

// 0x4F
// Armazena um int em um array.
void iastore(MethodData *method_data) {
    int *array_ref = (int *)stack_pop(method_data->frame_stack);
    int index = *((int *)stack_pop(method_data->frame_stack));
    int value = *((int *)stack_pop(method_data->frame_stack));
    array_ref[index] = value;
}

// 0x50
// Armazena um long em um array.
void lastore(MethodData *method_data) {
    long *array_ref = (long *)stack_pop(method_data->frame_stack);
    int index = *((int *)stack_pop(method_data->frame_stack));
    long value = *((long *)stack_pop(method_data->frame_stack));
    array_ref[index] = value;
}

// 0x51
// Armazena um float em um array.
void fastore(MethodData *method_data) {
    float *array_ref = (float *)stack_pop(method_data->frame_stack);
    int index = *((int *)stack_pop(method_data->frame_stack));
    float value = *((float *)stack_pop(method_data->frame_stack));
    array_ref[index] = value;
}

// 0x52
// Armazena um double em um array.
void dastore(MethodData *method_data) {
    double *array_ref = (double *)stack_pop(method_data->frame_stack);
    int index = *((int *)stack_pop(method_data->frame_stack));
    double value = *((double *)stack_pop(method_data->frame_stack));
    array_ref[index] = value;
}

// 0x53
// Armazena uma referência em um array de referências.
void aastore(MethodData *method_data) {
    void **array_ref = (void **)stack_pop(method_data->frame_stack);
    int index = *((int *)stack_pop(method_data->frame_stack));
    void *value = stack_pop(method_data->frame_stack);
    array_ref[index] = value;
}

// 0x54
// Armazena um byte ou boolean em um array.
void bastore(MethodData *method_data) {
    char *array_ref = (char *)stack_pop(method_data->frame_stack);
    int index = *((int *)stack_pop(method_data->frame_stack));
    char value = *((char *)stack_pop(method_data->frame_stack));
    array_ref[index] = value;
}

// 0x55
// Armazena um char em um array.
void castore(MethodData *method_data) {
    char *array_ref = (char *)stack_pop(method_data->frame_stack);
    int index = *((int *)stack_pop(method_data->frame_stack));
    char value = *((char *)stack_pop(method_data->frame_stack));
    array_ref[index] = value;
}

// 0x56
// Armazena um short em um array.
void sastore(MethodData *method_data) {
    short *array_ref = (short *)stack_pop(method_data->frame_stack);
    int index = *((int *)stack_pop(method_data->frame_stack));
    short value = *((short *)stack_pop(method_data->frame_stack));
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

    Frame *current_frame = stack_top(method_data->frame_stack);

    u2 class_index = current_frame->constant_pool[index - 1].info.Fieldref.class_index;
    char class_name[300];
    get_class_name(class_index, current_frame->constant_pool, class_name);
    // // For debugging purposes
    printf("\t\tClass Name: %s\n", class_name);

    u2 name_type_index = current_frame->constant_pool[index - 1].info.Fieldref.name_and_type_index;
    u2 descriptor_index = current_frame->constant_pool[name_type_index - 1].info.NameAndType.descriptor_index;
    char descriptor_content[300];
    get_utf8_value(descriptor_index, current_frame->constant_pool, descriptor_content);
    // // For debugging purposes
    printf("\t\tDescription Content: %s\n", descriptor_content);

    method_data->pc += 2;
}
// 0xB3
void putstatic(MethodData *method_data)
{
}
// 0xB4
void getfield(MethodData *method_data)
{
}
// 0xB5
void putfield(MethodData *method_data)
{
}
// 0xB6
void invokevirtual(MethodData *method_data)
{
}
// 0xB7
void invokespecial(MethodData *method_data)
{
}
// 0xB8
void invokestatic(MethodData *method_data)
{
}
// 0xB9
void invokeinterface(MethodData *method_data)
{
}
// 0xBB (skipped 0xBA (186MethodData* method_data) - invokedynamicMethodData* method_data)
void new_func(MethodData *method_data)
{
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
