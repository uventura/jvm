#include "lib/interpreter/byte_code.h"
#include "lib/base/class_file/cp_info.h"
#include "lib/base/structures/stack.h"
#include "lib/runtime_data_area/frame.h"
#include "lib/runtime_data_area/method_area.h"

#include <string.h>
#include <stdlib.h>

// Functions for the opcode.

// 0x00
void nop(MethodData *method_data)
{
    // Não realiza nenhuma operação.
}

// 0x01
void aconst_null(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    stack_push(current_frame->operand_stack, NULL);
}

// 0x02
void iconst_m1(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int *value = (int *)malloc(sizeof(int));
    *value = -1;
    stack_push(current_frame->operand_stack, value);
}

// 0x03
void iconst_0(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int *value = (int *)malloc(sizeof(int));
    *value = 0;
    stack_push(current_frame->operand_stack, value);
}

// 0x04
void iconst_1(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int *value = (int *)malloc(sizeof(int));
    *value = 1;
    stack_push(current_frame->operand_stack, value);
}

// 0x05
void iconst_2(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int *value = (int *)malloc(sizeof(int));
    *value = 2;
    stack_push(current_frame->operand_stack, value);
}

// 0x06
void iconst_3(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int *value = (int *)malloc(sizeof(int));
    *value = 3;
    stack_push(current_frame->operand_stack, value);
}

// 0x07
void iconst_4(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int *value = (int *)malloc(sizeof(int));
    *value = 4;
    stack_push(current_frame->operand_stack, value);
}

// 0x08
void iconst_5(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int *value = (int *)malloc(sizeof(int));
    *value = 5;
    stack_push(current_frame->operand_stack, value);
}

// 0x09
void lconst_0(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    long *value = (long *)malloc(sizeof(long));
    *value = 0;
    stack_push(current_frame->operand_stack, value);
}
// 0x0A
void lconst_1(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    long *value = (long *)malloc(sizeof(long));
    *value = 1;
    stack_push(current_frame->operand_stack, value);
}

// 0x0B
void fconst_0(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    float *value = (float *)malloc(sizeof(float));
    *value = 0.0f;
    stack_push(current_frame->operand_stack, value);
}

// 0x0C
void fconst_1(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    float *value = (float *)malloc(sizeof(float));
    *value = 1.0f;
    stack_push(current_frame->operand_stack, value);
}

// 0x0D
void fconst_2(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    float *value = (float *)malloc(sizeof(float));
    *value = 2.0f;
    stack_push(current_frame->operand_stack, value);
}

// 0x0E
void dconst_0(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    double *value = (double *)malloc(sizeof(double));
    *value = 0.0;
    stack_push(current_frame->operand_stack, value);
}

// 0x0F
void dconst_1(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    double *value = (double *)malloc(sizeof(double));
    *value = 1.0;
    stack_push(current_frame->operand_stack, value);
}

// 0x10
void bipush(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int *value = (int *)malloc(sizeof(int));
    *value = (int)method_data->code.code[method_data->pc + 1];
    stack_push(current_frame->operand_stack, value);
    method_data->pc += 1;
}

// 0x11
void sipush(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
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
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    u2 index = method_data->code.code[method_data->pc + 1];
    cp_info element = current_frame->constant_pool[index - 1];

    if (element.tag == CONSTANT_String)
    {
        u2 utf8_index = current_frame->constant_pool[index - 1].info.String.string_index;
    char utf8_buffer[256];  // Alocando buffer. Tamanho pode ser ajustado conforme necessário.
        get_utf8_value(utf8_index, current_frame->constant_pool, utf8_buffer);
        stack_push(current_frame->operand_stack, utf8_buffer);
    }

    method_data->pc += 2;
}

// 0x13
void ldc_w(MethodData *method_data)
{
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    u2 index = read_u2(&method_data->code.code[method_data->pc + 1]);
    cp_info element = current_frame->constant_pool[index - 1];

    if (element.tag == CONSTANT_String)
    {
        u2 utf8_index = current_frame->constant_pool[index - 1].info.String.string_index;
    char utf8_buffer[256];  // Alocando buffer. Tamanho pode ser ajustado conforme necessário.
        get_utf8_value(utf8_index, current_frame->constant_pool, utf8_buffer);
        stack_push(current_frame->operand_stack, utf8_buffer);
    }

    method_data->pc += 3;
}

// 0x14
void ldc2_w(MethodData *method_data)
{
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    u2 index = read_u2(&method_data->code.code[method_data->pc + 1]);
    cp_info element = current_frame->constant_pool[index - 1];

    if (element.tag == CONSTANT_Long)
    {
        CONSTANT_Long_info long_element = element.info.Long;
        long long_value = ((long)long_element.high_bytes << 32) | long_element.low_bytes;
    }
    else if (element.tag == CONSTANT_Double)
    {
        CONSTANT_Double_info double_element = element.info.Double;
        double double_value;
    }

    method_data->pc += 3;
}


// 0x15
void iload(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    u1 index = method_data->code.code[method_data->pc + 1];
    int *buffer  = (int *)malloc(sizeof(int));
    int *value  = (int *)(current_frame->local_variables[index]);
    stack_push(current_frame->operand_stack, buffer);
    method_data->pc += 2;
}

// 0x16
void lload(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    u1 index = method_data->code.code[method_data->pc + 1];
    long *buffer  = (long *)malloc(sizeof(long));
     *value  = (long *)(current_frame->local_variables[index]);
    stack_push(current_frame->operand_stack, buffer);
    method_data->pc += 2;
}

// 0x17
void fload(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    u1 index = method_data->code.code[method_data->pc + 1];
    float *buffer  = (float *)malloc(sizeof(float));
    float *value  = (float *)(current_frame->local_variables[index]);
    stack_push(current_frame->operand_stack, buffer);
    method_data->pc += 2;
}

// 0x18
void dload(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    u1 index = method_data->code.code[method_data->pc + 1];
    double *buffer  = (double *)malloc(sizeof(double));
     double *value  = (double *)(current_frame->local_variables[index]);
    stack_push(current_frame->operand_stack, buffer);
    method_data->pc += 2;
}

// 0x19
void aload(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    u1 index = method_data->code.code[method_data->pc + 1];
    void *buffer  = (double *)malloc(sizeof(double));
    void *ref  = current_frame->local_variables[index];
    stack_push(current_frame->operand_stack, buffer);
    method_data->pc += 2;
}

// 0x1A
void iload_0(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int *buffer  = (int *)malloc(sizeof(int));
   int *value  = (int *)(current_frame->local_variables[0]);
    stack_push(current_frame->operand_stack, buffer);
}

// 0x1B
void iload_1(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int *buffer  = (int *)malloc(sizeof(int));
    int *value  = (int *)(current_frame->local_variables[1]);
    stack_push(current_frame->operand_stack, buffer);
}


// 0x1C
void iload_2(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int *buffer  = (int *)malloc(sizeof(int));
     int *value  = (int *)(current_frame->local_variables[2]);
    stack_push(current_frame->operand_stack, buffer);
}

// 0x1D
void iload_3(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    int *buffer  = (int *)malloc(sizeof(int));
     int *value  = (int *)(current_frame->local_variables[3]);
    stack_push(current_frame->operand_stack, buffer);
}

// 0x1E
void lload_0(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    long *buffer  = (long *)malloc(sizeof(long));
    long *value  = (long *)(current_frame->local_variables[0]);
    stack_push(current_frame->operand_stack, buffer);
}

// 0x1F
void lload_1(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    long *buffer  = (long *)malloc(sizeof(long));
    long *value  = (long *)(current_frame->local_variables[1]);
    stack_push(current_frame->operand_stack, buffer);
}

// 0x20
void lload_2(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    long *buffer  = (long *)malloc(sizeof(long));
    long *value  = (long *)(current_frame->local_variables[2]);
    stack_push(current_frame->operand_stack, buffer);
}

// 0x21
void lload_3(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    long *buffer  = (long *)malloc(sizeof(long));
    long *value  = (long *)(current_frame->local_variables[3]);
    stack_push(current_frame->operand_stack, buffer);
}

// 0x22
void fload_0(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    float *buffer  = (float *)malloc(sizeof(float));
    float *value  = (float *)(current_frame->local_variables[0]);
    stack_push(current_frame->operand_stack, buffer);
}

// 0x23
void fload_1(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    float *buffer  = (float *)malloc(sizeof(float));
   float *value  = (float *)(current_frame->local_variables[1]);
    stack_push(current_frame->operand_stack, buffer);
}

// 0x24
void fload_2(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    float *buffer  = (float *)malloc(sizeof(float));
      float *value  = (float *)(current_frame->local_variables[2]);
    stack_push(current_frame->operand_stack, buffer);
}

// 0x25
void fload_3(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    float *buffer  = (float *)malloc(sizeof(float));
     float *value  = (float *)(current_frame->local_variables[3]);
    stack_push(current_frame->operand_stack, buffer);
}

// 0x26
void dload_0(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    double *buffer  = (double *)malloc(sizeof(double));
      double *value  = (double *)(current_frame->local_variables[0]);
    stack_push(current_frame->operand_stack, buffer);
}

// 0x27
void dload_1(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    double *buffer  = (double *)malloc(sizeof(double));
        double *value  = (double *)(current_frame->local_variables[1]);
    stack_push(current_frame->operand_stack, buffer);
}

// 0x28
void dload_2(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    double *buffer  = (double *)malloc(sizeof(double));
       double *value  = (double *)(current_frame->local_variables[2]);
    stack_push(current_frame->operand_stack, buffer);
}

// 0x29
void dload_3(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    double *buffer  = (double *)malloc(sizeof(double));
      double *value  = (double *)(current_frame->local_variables[3]);
    stack_push(current_frame->operand_stack, buffer);
}

// 0x2A
void aload_0(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    void *buffer  = (double *)malloc(sizeof(double));
       void *value  = current_frame->local_variables[0];
    stack_push(current_frame->operand_stack, buffer);
}

// 0x2B
void aload_1(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    void *buffer  = (double *)malloc(sizeof(double));
       void *value  = current_frame->local_variables[1];
    stack_push(current_frame->operand_stack, buffer);
}

// 0x2C
void aload_2(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    void *buffer  = (double *)malloc(sizeof(double));
       void *value  = current_frame->local_variables[2];
    stack_push(current_frame->operand_stack, buffer);
}

// 0x2D
void aload_3(MethodData *method_data)
{
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    void *buffer  = (double *)malloc(sizeof(double));
       void *value  = current_frame->local_variables[3];
    stack_push(current_frame->operand_stack, buffer);
}

// Carrega um inteiro de um array especificado pelo índice e pela referência do array na pilha de operandos.
void iaload(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *array_ref_node = (Node *)stack_top(current_frame->operand_stack);
    int *array_ref = *((int **)(array_ref_node->data));
    stack_pop(current_frame->operand_stack);

    int value = array_ref[index];
    stack_push(current_frame->operand_stack, &value);
}

// 0x2F
// Carrega um long de um array especificado pelo índice e pela referência do array na pilha de operandos.
void laload(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *array_ref_node = (Node *)stack_top(current_frame->operand_stack);
    long *array_ref = *((long **)(array_ref_node->data));
    stack_pop(current_frame->operand_stack);

    long value = array_ref[index];
    stack_push(current_frame->operand_stack, &value);
}

// 0x30
// Carrega um float de um array especificado pelo índice e pela referência do array na pilha de operandos.
void faload(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *array_ref_node = (Node *)stack_top(current_frame->operand_stack);
    float *array_ref = *((float **)(array_ref_node->data));
    stack_pop(current_frame->operand_stack);

    float value = array_ref[index];
    stack_push(current_frame->operand_stack, &value);
}

// 0x31
// Carrega um double de um array especificado pelo índice e pela referência do array na pilha de operandos.
void daload(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *array_ref_node = (Node *)stack_top(current_frame->operand_stack);
    double *array_ref = *((double **)(array_ref_node->data));
    stack_pop(current_frame->operand_stack);

    double value = array_ref[index];
    stack_push(current_frame->operand_stack, &value);
}

// 0x32
// Carrega uma referência de um array de referências especificado pelo índice e pela referência do array na pilha de operandos.
void aaload(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *array_ref_node = (Node *)stack_top(current_frame->operand_stack);
    void **array_ref = *((void ***)(array_ref_node->data));
    stack_pop(current_frame->operand_stack);

    void *value = array_ref[index];
    stack_push(current_frame->operand_stack, &value);
}

// 0x33
// Carrega um byte ou boolean de um array especificado pelo índice e pela referência do array na pilha de operandos.
void baload(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *array_ref_node = (Node *)stack_top(current_frame->operand_stack);
    char *array_ref = *((char **)(array_ref_node->data));
    stack_pop(current_frame->operand_stack);

    char value = array_ref[index];
    stack_push(current_frame->operand_stack, &value);
}

// 0x34
// Carrega um char de um array especificado pelo índice e pela referência do array na pilha de operandos.
void caload(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *array_ref_node = (Node *)stack_top(current_frame->operand_stack);
    char *array_ref = *((char **)(array_ref_node->data));
    stack_pop(current_frame->operand_stack);

    char value = array_ref[index];
    stack_push(current_frame->operand_stack, &value);
}

// 0x35
// Carrega um short de um array especificado pelo índice e pela referência do array na pilha de operandos.
void saload(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *array_ref_node = (Node *)stack_top(current_frame->operand_stack);
    short *array_ref = *((short **)(array_ref_node->data));
    stack_pop(current_frame->operand_stack);

    short value = array_ref[index];
    stack_push(current_frame->operand_stack, &value);
}


// 0x36
// Armazena um int de uma variável local ou da stack de operandos em um array.
void istore(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    // Obtendo o índice da pilha de operandos
    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    // Obtendo o valor a ser armazenado
    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    int value = *((int *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    // Armazenando o valor na variável local
    current_frame->local_variables[index]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[index]  = value;
}

// 0x37
// Armazena um long de uma variável local ou da stack de operandos em um array.
void lstore(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    long value = *((long *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[index]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[index]  = value;
}

// 0x38
// Armazena um float de uma variável local ou da stack de operandos em um array.
void fstore(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    float value = *((float *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[index]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[index]  = value;
}

// 0x39
// Armazena um double de uma variável local ou da stack de operandos em um array.
void dstore(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    double value = *((double *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[index]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[index]  = value;
}


// 0x3A
// Armazena uma referência de uma variável local ou da stack de operandos em um array.
void astore(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    void *value = value_node->data;
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[index]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[index]  = value;
}


// 0x3B
// Armazena um int na primeira posição das variáveis locais.
void istore_0(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    int value = *((int *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[0]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[0]  = value;
}
// 0x3C
// Armazena um int na segunda posição das variáveis locais.
void istore_1(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    int value = *((int *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[1]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[1]  = value;
}

// 0x3D
// Armazena um int na terceira posição das variáveis locais.
void istore_2(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    int value = *((int *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[2]  = (double *)malloc(sizeof(double));
    double * = (current_frame->local_variables[2]  = value;
}
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    long value = *((long *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[0]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[0]  = value;
}

// 0x3E
// Armazena um int na quarta posição das variáveis locais.
void istore_3(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    int value = *((int *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[3]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[3]  = value;
}

// 0x3F
// Armazena um long na primeira posição das variáveis locais.
void lstore_0(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    long value = *((long *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[0]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[0]  = value;
}

// 0x40
// Armazena um long na segunda posição das variáveis locais.
void lstore_1(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    long value = *((long *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[1]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[1]  = value;
}

// 0x41
// Armazena um long na terceira posição das variáveis locais.
void lstore_2(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    long value = *((long *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[2]  = (double *)malloc(sizeof(double));
    double * = (current_frame->local_variables[2]  = value;
}

// 0x42
// Armazena um long na quarta posição das variáveis locais.
void lstore_3(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    long value = *((long *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[3]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[3]  = value;
}

// 0x43
// Armazena um float na primeira posição das variáveis locais.
void fstore_0(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    float value = *((float *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[0]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[0]  = value;
}

// 0x44
// Armazena um float na segunda posição das variáveis locais.
void fstore_1(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    float value = *((float *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[1]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[1]  = value;
}

// 0x45
// Armazena um float na terceira posição das variáveis locais.
void fstore_2(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    float value = *((float *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[2]  = (double *)malloc(sizeof(double));
    double * = (current_frame->local_variables[2]  = value;
}

// 0x46
// Armazena um float na quarta posição das variáveis locais.
void fstore_3(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    float value = *((float *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[3]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[3]  = value;
}

// 0x47
// Armazena um double na primeira posição das variáveis locais.
void dstore_0(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    double value = *((double *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[0]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[0]  = value;
}

// 0x48
// Armazena um double na segunda posição das variáveis locais.
void dstore_1(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    double value = *((double *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[1]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[1]  = value;
}

// 0x49
// Armazena um double na terceira posição das variáveis locais.
void dstore_2(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    double value = *((double *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[2]  = (double *)malloc(sizeof(double));
    double * = (current_frame->local_variables[2]  = value;
}

// 0x4A
// Armazena um double na quarta posição das variáveis locais.
void dstore_3(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    double value = *((double *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[3]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[3]  = value;
}
// 0x4B
// Armazena uma referência na primeira posição das variáveis locais.
void astore_0(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    void *value = value_node->data;
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[0]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[0]  = value;
}
// 0x4C
// Armazena uma referência na segunda posição das variáveis locais.
void astore_1(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    void *value = value_node->data;
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[1]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[1]  = value;
}

// 0x4D
// Armazena uma referência na terceira posição das variáveis locais.
void astore_2(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    void *value = value_node->data;
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[2]  = (double *)malloc(sizeof(double));
    double * = (current_frame->local_variables[2]  = value;
}

// 0x4E
// Armazena uma referência na quarta posição das variáveis locais.
void astore_3(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    void *value = value_node->data;
    stack_pop(current_frame->operand_stack);

    current_frame->local_variables[3]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[3]  = value;
}

// 0x4F
// iastore
void iastore(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    int value = *((int *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *array_ref_node = (Node *)stack_top(current_frame->operand_stack);
    int *array_ref = *((int **)(array_ref_node->data));
    stack_pop(current_frame->operand_stack);

    array_ref[index] = value;
}

// lastore
void lastore(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    long value = *((long *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *array_ref_node = (Node *)stack_top(current_frame->operand_stack);
    long *array_ref = *((long **)(array_ref_node->data));
    stack_pop(current_frame->operand_stack);

    array_ref[index] = value;
}

// fastore
void fastore(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    float value = *((float *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *array_ref_node = (Node *)stack_top(current_frame->operand_stack);
    float *array_ref = *((float **)(array_ref_node->data));
    stack_pop(current_frame->operand_stack);

    array_ref[index] = value;
}

// dastore
void dastore(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    double value = *((double *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *array_ref_node = (Node *)stack_top(current_frame->operand_stack);
    double *array_ref = *((double **)(array_ref_node->data));
    stack_pop(current_frame->operand_stack);

    array_ref[index] = value;
}

// aastore
void aastore(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    void *value = value_node->data;
    stack_pop(current_frame->operand_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *array_ref_node = (Node *)stack_top(current_frame->operand_stack);
    void **array_ref = *((void ***)(array_ref_node->data));
    stack_pop(current_frame->operand_stack);

    array_ref[index] = value;
}

// bastore
void bastore(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    char value = *((char *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *array_ref_node = (Node *)stack_top(current_frame->operand_stack);
    char *array_ref = *((char **)(array_ref_node->data));
    stack_pop(current_frame->operand_stack);

    array_ref[index] = value;
}

// castore
void castore(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    char value = *((char *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *array_ref_node = (Node *)stack_top(current_frame->operand_stack);
    char *array_ref = *((char **)(array_ref_node->data));
    stack_pop(current_frame->operand_stack);

    array_ref[index] = value;
}

// sastore
void sastore(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);

    Node *value_node = (Node *)stack_top(current_frame->operand_stack);
    short value = *((short *)(value_node->data));
    stack_pop(current_frame->operand_stack);

    Node *index_node = (Node *)stack_top(current_frame->operand_stack);
    int index = *((int *)(index_node->data));
    stack_pop(current_frame->operand_stack);

    Node *array_ref_node = (Node *)stack_top(current_frame->operand_stack);
    short *array_ref = *((short **)(array_ref_node->data));
    stack_pop(current_frame->operand_stack);

    array_ref[index] = value;
}


// 0x57 (optional implementation?MethodData* method_data)
// Remove o valor do topo da pilha de operandos.
void pop(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    stack_pop(current_frame->operand_stack);
}

// 0x58 (optional implementation?MethodData* method_data)
// Remove os dois valores do topo da pilha de operandos.
void pop2(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    stack_pop(current_frame->operand_stack);
    stack_pop(current_frame->operand_stack);
}

// 0x59 (optional implementation?MethodData* method_data)
// Duplica o valor do topo da pilha de operandos.
void dup(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    void *value = stack_top(current_frame->operand_stack);
    stack_push(current_frame->operand_stack, value);
}

// 0x5A (optional implementation?MethodData* method_data)
// Duplica o valor do topo da pilha de operandos e insere duas posições abaixo.
void dup_x1(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    Node *value1_node = (Node *)stack_top(current_frame->operand_stack);
    void *value1 = value1_node->data;
    stack_pop(current_frame->operand_stack);
    
    Node *value2_node = (Node *)stack_top(current_frame->operand_stack);
    void *value2 = value2_node->data;
    stack_pop(current_frame->operand_stack);
    
    stack_push(current_frame->operand_stack, value1);
    stack_push(current_frame->operand_stack, value2);
    stack_push(current_frame->operand_stack, value1);
}


// 0x5B (optional implementation?MethodData* method_data)
// Duplica o valor do topo da pilha de operandos e insere três ou duas posições abaixo.
void dup_x2(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    Node *value1_node = (Node *)stack_top(current_frame->operand_stack);
    void *value1 = value1_node->data;
    stack_pop(current_frame->operand_stack);
    
    Node *value2_node = (Node *)stack_top(current_frame->operand_stack);
    void *value2 = value2_node->data;
    stack_pop(current_frame->operand_stack);
    
    Node *value3_node = (Node *)stack_top(current_frame->operand_stack);
    void *value3 = value3_node->data;
    stack_pop(current_frame->operand_stack);
    
    stack_push(current_frame->operand_stack, value1);
    stack_push(current_frame->operand_stack, value3);
    stack_push(current_frame->operand_stack, value2);
    stack_push(current_frame->operand_stack, value1);
}


// 0x5C (optional implementation?MethodData* method_data)
// Duplica os dois valores do topo da pilha de operandos.
void dup2(MethodData *method_data) {
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    Node *value1_node = (Node *)stack_top(current_frame->operand_stack);
    void *value1 = value1_node->data;
    stack_pop(current_frame->operand_stack);

    Node *value2_node = (Node *)stack_top(current_frame->operand_stack);
    void *value2 = value2_node->data;
    stack_pop(current_frame->operand_stack);

    stack_push(current_frame->operand_stack, value2);
    stack_push(current_frame->operand_stack, value1);
    stack_push(current_frame->operand_stack, value2);
    stack_push(current_frame->operand_stack, value1);
}


// 0x5D (optional implementation?MethodData* method_data)
// Duplica os dois valores do topo da pilha de operandos e insere três posições abaixo.
void dup2_x1(MethodData *method_data) {
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    Node *value1_node = (Node *)stack_top(current_frame->operand_stack);
    void *value1 = value1_node->data;
    stack_pop(current_frame->operand_stack);

    Node *value2_node = (Node *)stack_top(current_frame->operand_stack);
    void *value2 = value2_node->data;
    stack_pop(current_frame->operand_stack);

    Node *value3_node = (Node *)stack_top(current_frame->operand_stack);
    void *value3 = value3_node->data;
    stack_pop(current_frame->operand_stack);

    stack_push(current_frame->operand_stack, value2);
    stack_push(current_frame->operand_stack, value1);
    stack_push(current_frame->operand_stack, value3);
    stack_push(current_frame->operand_stack, value2);
    stack_push(current_frame->operand_stack, value1);
}


// 0x5E (optional implementation?MethodData* method_data)
// Duplica os dois valores do topo da pilha de operandos e insere quatro ou três posições abaixo.
void dup2_x2(MethodData *method_data) {
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    Node *value1_node = (Node *)stack_top(current_frame->operand_stack);
    void *value1 = value1_node->data;
    stack_pop(current_frame->operand_stack);

    Node *value2_node = (Node *)stack_top(current_frame->operand_stack);
    void *value2 = value2_node->data;
    stack_pop(current_frame->operand_stack);

    Node *value3_node = (Node *)stack_top(current_frame->operand_stack);
    void *value3 = value3_node->data;
    stack_pop(current_frame->operand_stack);

    Node *value4_node = (Node *)stack_top(current_frame->operand_stack);
    void *value4 = value4_node->data;
    stack_pop(current_frame->operand_stack);

    stack_push(current_frame->operand_stack, value2);
    stack_push(current_frame->operand_stack, value1);
    stack_push(current_frame->operand_stack, value4);
    stack_push(current_frame->operand_stack, value3);
    stack_push(current_frame->operand_stack, value2);
    stack_push(current_frame->operand_stack, value1);
}


// 0x5F (optional implementation?MethodData* method_data)
// Troca os dois valores do topo da pilha de operandos.
void swap(MethodData *method_data) {
    Frame *current_frame = (Frame *)stack_top(method_data->frame_stack);
    Node *value1_node = (Node *)stack_top(current_frame->operand_stack);
    void *value1 = value1_node->data;
    stack_pop(current_frame->operand_stack);

    Node *value2_node = (Node *)stack_top(current_frame->operand_stack);
    void *value2 = value2_node->data;
    stack_pop(current_frame->operand_stack);

    stack_push(current_frame->operand_stack, value1);
    stack_push(current_frame->operand_stack, value2);
}


// 0x60
// Realiza a operação de adição de dois inteiros da pilha de operandos.
void iadd(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int value1 = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int value2 = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int result = value1 + value2;
    stack_push(current_frame->operand_stack, &result);
}

// 0x61
// Realiza a operação de adição de dois longs da pilha de operandos.
void ladd(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    long value1 = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long value2 = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long result = value1 + value2;
    stack_push(current_frame->operand_stack, &result);
}

// 0x62
// Realiza a operação de adição de dois floats da pilha de operandos.
void fadd(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    float value1 = void *temp = stack_top(current_frame->operand_stack);
    (float * value = *(((float * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    float value2 = void *temp = stack_top(current_frame->operand_stack);
    (float * value = *(((float * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    float result = value1 + value2;
    stack_push(current_frame->operand_stack, &result);
}

// 0x63
// Realiza a operação de adição de dois doubles da pilha de operandos.
void dadd(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    double value1 = void *temp = stack_top(current_frame->operand_stack);
    (double * value = *(((double * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    double value2 = void *temp = stack_top(current_frame->operand_stack);
    (double * value = *(((double * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    double result = value1 + value2;
    stack_push(current_frame->operand_stack, &result);
}

// 0x64
// Realiza a operação de subtração de dois inteiros da pilha de operandos.
void isub(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int value1 = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int value2 = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int result = value1 - value2;
    stack_push(current_frame->operand_stack, &result);
}

// 0x65
// Realiza a operação de subtração de dois longs da pilha de operandos.
void lsub(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    long value1 = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long value2 = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long result = value1 - value2;
    stack_push(current_frame->operand_stack, &result);
}

// 0x66
// Realiza a operação de subtração de dois floats da pilha de operandos.
void fsub(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    float value1 = void *temp = stack_top(current_frame->operand_stack);
    (float * value = *(((float * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    float value2 = void *temp = stack_top(current_frame->operand_stack);
    (float * value = *(((float * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    float result = value1 - value2;
    stack_push(current_frame->operand_stack, &result);
}

// 0x67
// Realiza a operação de subtração de dois doubles da pilha de operandos.
void dsub(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    double value1 = void *temp = stack_top(current_frame->operand_stack);
    (double * value = *(((double * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    double value2 = void *temp = stack_top(current_frame->operand_stack);
    (double * value = *(((double * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    double result = value1 - value2;
    stack_push(current_frame->operand_stack, &result);
}

// 0x68
// Realiza a operação de multiplicação de dois inteiros da pilha de operandos.
void imul(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int value1 = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int value2 = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int result = value1 * value2;
    stack_push(current_frame->operand_stack, &result);
}

// 0x69
// Realiza a operação de multiplicação de dois longs da pilha de operandos.
void lmul(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    long value1 = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long value2 = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long result = value1 * value2;
    stack_push(current_frame->operand_stack, &result);
}

// 0x6A
// Realiza a operação de multiplicação de dois floats da pilha de operandos.
void fmul(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    float value1 = void *temp = stack_top(current_frame->operand_stack);
    (float * value = *(((float * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    float value2 = void *temp = stack_top(current_frame->operand_stack);
    (float * value = *(((float * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    float result = value1 * value2;
    stack_push(current_frame->operand_stack, &result);
}

// 0x6B
// Realiza a operação de multiplicação de dois doubles da pilha de operandos.
void dmul(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    double value1 = void *temp = stack_top(current_frame->operand_stack);
    (double * value = *(((double * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    double value2 = void *temp = stack_top(current_frame->operand_stack);
    (double * value = *(((double * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    double result = value1 * value2;
    stack_push(current_frame->operand_stack, &result);
}

// 0x6C
// Realiza a divisão de dois inteiros da pilha de operandos.
void idiv(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int divisor = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int dividend = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int result = dividend / divisor;
    stack_push(current_frame->operand_stack, &result);
}

// 0x6D
// Realiza a divisão de dois longs da pilha de operandos.
void ldiv_func(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    long divisor = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long dividend = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long result = dividend / divisor;
    stack_push(current_frame->operand_stack, &result);
}

// 0x6E
// Realiza a divisão de dois floats da pilha de operandos.
void fdiv(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    float divisor = void *temp = stack_top(current_frame->operand_stack);
    (float * value = *(((float * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    float dividend = void *temp = stack_top(current_frame->operand_stack);
    (float * value = *(((float * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    float result = dividend / divisor;
    stack_push(current_frame->operand_stack, &result);
}

// 0x6F
// Realiza a divisão de dois doubles da pilha de operandos.
void ddiv(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    double divisor = void *temp = stack_top(current_frame->operand_stack);
    (double * value = *(((double * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    double dividend = void *temp = stack_top(current_frame->operand_stack);
    (double * value = *(((double * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    double result = dividend / divisor;
    stack_push(current_frame->operand_stack, &result);
}

// 0x70
// Realiza a operação de resto de divisão de dois inteiros da pilha de operandos.
void irem(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int divisor = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int dividend = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int result = dividend % divisor;
    stack_push(current_frame->operand_stack, &result);
}

// 0x71
// Realiza a operação de resto de divisão de dois longs da pilha de operandos.
void lrem(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    long divisor = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long dividend = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long result = dividend % divisor;
    stack_push(current_frame->operand_stack, &result);
}

// 0x72
// Realiza a operação de resto de divisão de dois floats da pilha de operandos.
void frem(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    float divisor = void *temp = stack_top(current_frame->operand_stack);
    (float * value = *(((float * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    float dividend = void *temp = stack_top(current_frame->operand_stack);
    (float * value = *(((float * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    float result = fmodf(dividend, divisor);
    stack_push(current_frame->operand_stack, &result);
}

// 0x73
// Realiza a operação de resto de divisão de dois doubles da pilha de operandos.
void drem(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    double divisor = void *temp = stack_top(current_frame->operand_stack);
    (double * value = *(((double * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    double dividend = void *temp = stack_top(current_frame->operand_stack);
    (double * value = *(((double * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    double result = fmod(dividend, divisor);
    stack_push(current_frame-> operand_stack, &result);
}

// 0x74
// Realiza a operação de negação de um inteiro da pilha de operandos.
void ineg(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int value = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int result = -value;
    stack_push(current_frame->operand_stack, &result);
}

// 0x75
// Realiza a operação de negação de um long da pilha de operandos.
void lneg(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    long value = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long result = -value;
    stack_push(current_frame->operand_stack, &result);
}

// 0x76
// Realiza a operação de negação de um float da pilha de operandos.
void fneg(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    float value = void *temp = stack_top(current_frame->operand_stack);
    (float * value = *(((float * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    float result = -value;
    stack_push(current_frame->operand_stack, &result);
}

// 0x77
// Realiza a operação de negação de um double da pilha de operandos.
void dneg(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    double value = void *temp = stack_top(current_frame->operand_stack);
    (double * value = *(((double * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    double result = -value;
    stack_push(current_frame->operand_stack, &result);
}

// 0x78
// Realiza a operação de shift à esquerda em um inteiro da pilha de operandos.
void ishl(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int shift = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int value = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int result = value << shift;
    stack_push(current_frame->operand_stack, &result);
}

// 0x79
// Realiza a operação de shift à esquerda em um long da pilha de operandos.
void lshl(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int shift = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long value = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long result = value << shift;
    stack_push(current_frame->operand_stack, &result);
}

// 0x7A
// Realiza a operação de shift à direita em um inteiro da pilha de operandos.
void ishr(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int shift = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int value = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int result = value >> shift;
    stack_push(current_frame->operand_stack, &result);
}

// 0x7B
// Realiza a operação de shift à direita em um long da pilha de operandos.
void lshr(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int shift = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long value = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long result = value >> shift;
    stack_push(current_frame->operand_stack, &result);
}

// 0x7C
// Realiza a operação de deslocamento lógico à direita sem sinal (unsigned shift right) de um inteiro.
void iushr(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int value = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int shift = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack)) & 0x1F;  // Use apenas os 5 bits inferiores
    int result = value >> shift;
    stack_push(current_frame->operand_stack, &result);
}

// 0x7D
// Realiza a operação de deslocamento lógico à direita sem sinal (unsigned shift right) de um long.
void lushr(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    long value = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int shift = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack)) & 0x3F;  // Use apenas os 6 bits inferiores
    long result = value >> shift;
    stack_push(current_frame->operand_stack, &result);
}

// 0x7E
// Realiza a operação de AND bit a bit entre dois inteiros.
void iand(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int value1 = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int value2 = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int result = value1 & value2;
    stack_push(current_frame->operand_stack, &result);
}

// 0x7F
// Realiza a operação de AND bit a bit entre dois longs.
void land(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    long value1 = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long value2 = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long result = value1 & value2;
    stack_push(current_frame->operand_stack, &result);
}

// 0x80
// Realiza a operação de OR bit a bit entre dois inteiros.
void ior(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int value1 = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int value2 = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int result = value1 | value2;
    stack_push(current_frame->operand_stack, &result);
}

// 0x81
// Realiza a operação de OR bit a bit entre dois longs.
void lor(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    long value1 = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long value2 = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long result = value1 | value2;
    stack_push(current_frame->operand_stack, &result);
}

// 0x82
// Realiza a operação de XOR bit a bit entre dois inteiros.
void ixor(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int value1 = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int value2 = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int result = value1 ^ value2;
    stack_push(current_frame->operand_stack, &result);
}

// 0x83
// Realiza a operação de XOR bit a bit entre dois longs.
void lxor(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    long value1 = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long value2 = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long result = value1 ^ value2;
    stack_push(current_frame->operand_stack, &result);
}

// 0x84
// Incrementa uma variável local (int) por uma quantidade constante.
void iinc(MethodData *method_data, int index, int constant) {
    int value  = (int *)malloc(sizeof(int));
    *(int *)    int value  = *((int *)current_frame->local_variables[index]);
    value += constant;
    current_frame->local_variables[index]  = (double *)malloc(sizeof(double));
    *(double *)    current_frame->local_variables[index]  = value;
}

// 0x85
// Converte um int da pilha de operandos em um long e empurra o resultado de volta para a pilha.
void i2l(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int value = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long result = (long)value;
    stack_push(current_frame->operand_stack, &result);
}

// 0x86
// Converte um int da pilha de operandos em um float e empurra o resultado de volta para a pilha.
void i2f(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int value = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    float result = (float)value;
    stack_push(current_frame->operand_stack, &result);
}

// 0x87
// Converte um int da pilha de operandos em um double e empurra o resultado de volta para a pilha.
void i2d(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int value = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    double result = (double)value;
    stack_push(current_frame->operand_stack, &result);
}

// 0x88
// Converte um long da pilha de operandos em um int e empurra o resultado de volta para a pilha.
void l2i(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    long value = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int result = (int)value;
    stack_push(current_frame->operand_stack, &result);
}

// 0x89
// Converte um long da pilha de operandos em um float e empurra o resultado de volta para a pilha.
void l2f(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    long value = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    float result = (float)value;
    stack_push(current_frame->operand_stack, &result);
}

// 0x8A
// Converte um long da pilha de operandos em um double e empurra o resultado de volta para a pilha.
void l2d(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    long value = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    double result = (double)value;
    stack_push(current_frame->operand_stack, &result);
}

// 0x8B
// Converte um float da pilha de operandos em um int e empurra o resultado de volta para a pilha.
void f2i(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    float value = void *temp = stack_top(current_frame->operand_stack);
    (float * value = *(((float * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int result = (int)value;
    stack_push(current_frame->operand_stack, &result);
}

// 0x8C
// Converte um float da pilha de operandos em um long e empurra o resultado de volta para a pilha.
void f2l(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    float value = void *temp = stack_top(current_frame->operand_stack);
    (float * value = *(((float * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long result = (long)value;
    stack_push(current_frame->operand_stack, &result);
}

// 0x8D
// Converte um float da pilha de operandos em um double e empurra o resultado de volta para a pilha.
void f2d(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    float value = void *temp = stack_top(current_frame->operand_stack);
    (float * value = *(((float * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    double result = (double)value;
    stack_push(current_frame->operand_stack, &result);
}

// 0x8E
// Converte um double da pilha de operandos em um int e empurra o resultado de volta para a pilha.
void d2i(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    double value = void *temp = stack_top(current_frame->operand_stack);
    (double * value = *(((double * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int result = (int)value;
    stack_push(current_frame->operand_stack, &result);
}

// 0x8F
// Converte um double da pilha de operandos em um long e empurra o resultado de volta para a pilha.
void d2l(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    double value = void *temp = stack_top(current_frame->operand_stack);
    (double * value = *(((double * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long result = (long)value;
    stack_push(current_frame->operand_stack, &result);
}

// 0x90
// Converte um double da pilha de operandos em um float e empurra o resultado de volta para a pilha.
void d2f(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    double value = void *temp = stack_top(current_frame->operand_stack);
    (double * value = *(((double * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    float result = (float)value;
    stack_push(current_frame->operand_stack, &result);
}

// 0x91
// Converte um int da pilha de operandos em um byte e empurra o resultado de volta para a pilha.
void i2b(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int value = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    char result = (char)value;
    stack_push(current_frame->operand_stack, &result);
}

// 0x92
// Converte um int da pilha de operandos em um char e empurra o resultado de volta para a pilha.
void i2c(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int value = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    char result = (char)value;
    stack_push(current_frame->operand_stack, &result);
}

// 0x93
// Converte um int da pilha de operandos em um short e empurra o resultado de volta para a pilha.
void i2s(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int value = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    short result = (short)value;
    stack_push(current_frame-> operand_stack, &result);
}

// 0x94
// Compara dois longs da pilha de operandos e empurra o resultado da comparação de volta para a pilha.
void lcmp(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    long value2 = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    long value1 = void *temp = stack_top(current_frame->operand_stack);
    (long * value = *(((long * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int result = (value1 > value2) ? 1 : ((value1 == value2) ? 0 : -1);
    stack_push(current_frame->operand_stack, &result);
}

// 0x95
// Compara dois floats da pilha de operandos e empurra o resultado da comparação de volta para a pilha, tratando NaN como menor.
void fcmpl(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    float value2 = void *temp = stack_top(current_frame->operand_stack);
    (float * value = *(((float * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    float value1 = void *temp = stack_top(current_frame->operand_stack);
    (float * value = *(((float * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int result;
    if (isnan(value1) || isnan(value2)) {
        result = -1;
    } else {
        result = (value1 > value2) ? 1 : ((value1 == value2) ? 0 : -1);
    }
    stack_push(current_frame->operand_stack, &result);
}

// 0x96
// Compara dois floats da pilha de operandos e empurra o resultado da comparação de volta para a pilha, tratando NaN como maior.
void fcmpg(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    float value2 = void *temp = stack_top(current_frame->operand_stack);
    (float * value = *(((float * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    float value1 = void *temp = stack_top(current_frame->operand_stack);
    (float * value = *(((float * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int result;
    if (isnan(value1) || isnan(value2)) {
        result = 1;
    } else {
        result = (value1 > value2) ? 1 : ((value1 == value2) ? 0 : -1);
    }
    stack_push(current_frame->operand_stack, &result);
}

// 0x97
// Compara dois doubles da pilha de operandos e empurra o resultado da comparação de volta para a pilha, tratando NaN como menor.
void dcmpl(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    double value2 = void *temp = stack_top(current_frame->operand_stack);
    (double * value = *(((double * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    double value1 = void *temp = stack_top(current_frame->operand_stack);
    (double * value = *(((double * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int result;
    if (isnan(value1) || isnan(value2)) {
        result = -1;
    } else {
        result = (value1 > value2) ? 1 : ((value1 == value2) ? 0 : -1);
    }
    stack_push(current_frame->operand_stack, &result);
}

// 0x98
// Compara dois doubles da pilha de operandos e empurra o resultado da comparação de volta para a pilha, tratando NaN como maior.
void dcmpg(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    double value2 = void *temp = stack_top(current_frame->operand_stack);
    (double * value = *(((double * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    double value1 = void *temp = stack_top(current_frame->operand_stack);
    (double * value = *(((double * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    int result;
    if (isnan(value1) || isnan(value2)) {
        result = 1;
    } else {
        result = (value1 > value2) ? 1 : ((value1 == value2) ? 0 : -1);
    }
    stack_push(current_frame->operand_stack, &result);
}

// 0x99
// Pula para o endereço do branch se o valor no topo da pilha de operandos é igual a zero.
void ifeq(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int value = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    if (value == 0) {
        u2 branchbyte1 = method_data->code.code[method_data->pc + 1];
        u2 branchbyte2 = method_data->code.code[method_data->pc + 2];
        short branch_offset = (short)((branchbyte1 << 8) | branchbyte2);
        method_data->pc += branch_offset;
    } else {
        method_data->pc += 3;  // Avança o PC além do opcode e dos dois bytes do deslocamento
    }
}

// 0x9A
// Pula para o endereço do branch se o valor no topo da pilha de operandos não é igual a zero.
void ifne(MethodData *method_data) {
    Frame *current_frame = (Frame *)(Frame *)stack_top(method_data->frame_stack);
    int value = void *temp = stack_top(current_frame->operand_stack);
    (int * value = *(((int * *)temp);
    stack_pop(current_frame->operand_stack);(current_frame->operand_stack));
    if (value != 0) {
        u2 branchbyte1 = method_data->code.code[method_data->pc + 1];
        u2 branchbyte2 = method_data->code.code[method_data->pc + 2];
        short branch_offset = (short)((branchbyte1 << 8) | branchbyte2);
        method_data->pc += branch_offset;
    } else {
        method_data->pc += 3;  // Avança o PC além do opcode e dos dois bytes do deslocamento
    }
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