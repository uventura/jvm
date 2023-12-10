#ifndef JVM_BYTE_CODE
#define JVM_BYTE_CODE

// Header defining the signatures of the bytecode operations.
// To be implemented: EXCLUDING 186 (invokedynamic), the opcodes 0 to 201.

#include "lib/runtime_data_area/method_area.h"

// 0x00
void nop(MethodData *method_data);
// 0x01
void aconst_null(MethodData *method_data);
// 0x02
void iconst_m1(MethodData *method_data);
// 0x03
void iconst_0(MethodData *method_data);
// 0x04
void iconst_1(MethodData *method_data);
// 0x05
void iconst_2(MethodData *method_data);
// 0x06
void iconst_3(MethodData *method_data);
// 0x07
void iconst_4(MethodData *method_data);
// 0x08
void iconst_5(MethodData *method_data);
// 0x09
void lconst_0(MethodData *method_data);
// 0x0A
void lconst_1(MethodData *method_data);
// 0x0B
void fconst_0(MethodData *method_data);
// 0x0C
void fconst_1(MethodData *method_data);
// 0x0D
void fconst_2(MethodData *method_data);
// 0x0E
void dconst_0(MethodData *method_data);
// 0x0F
void dconst_1(MethodData *method_data);
// 0x10
void bipush(MethodData *method_data);
// 0x11
void sipush(MethodData *method_data);
// 0x12
void ldc(MethodData *method_data);
// 0x13
void ldc_w(MethodData *method_data);
// 0x14
void ldc2_w(MethodData *method_data);
// 0x15
void iload(MethodData *method_data);
// 0x16
void lload(MethodData *method_data);
// 0x17
void fload(MethodData *method_data);
// 0x18
void dload(MethodData *method_data);
// 0x19
void aload(MethodData *method_data);
// 0x1A
void iload_0(MethodData *method_data);
// 0x1B
void iload_1(MethodData *method_data);
// 0x1C
void iload_2(MethodData *method_data);
// 0x1D
void iload_3(MethodData *method_data);
// 0x1E
void lload_0(MethodData *method_data);
// 0x1F
void lload_1(MethodData *method_data);
// 0x20
void lload_2(MethodData *method_data);
// 0x21
void lload_3(MethodData *method_data);
// 0x22
void fload_0(MethodData *method_data);
// 0x23
void fload_1(MethodData *method_data);
// 0x24
void fload_2(MethodData *method_data);
// 0x25
void fload_3(MethodData *method_data);
// 0x26
void dload_0(MethodData *method_data);
// 0x27
void dload_1(MethodData *method_data);
// 0x28
void dload_2(MethodData *method_data);
// 0x29
void dload_3(MethodData *method_data);
// 0x2A
void aload_0(MethodData *method_data);
// 0x2B
void aload_1(MethodData *method_data);
// 0x2C
void aload_2(MethodData *method_data);
// 0x2D
void aload_3(MethodData *method_data);
// 0x2E
void iaload(MethodData *method_data);
// 0x2F
void laload(MethodData *method_data);
// 0x30
void faload(MethodData *method_data);
// 0x31
void daload(MethodData *method_data);
// 0x32
void aaload(MethodData *method_data);
// 0x33
void baload(MethodData *method_data);
// 0x34
void caload(MethodData *method_data);
// 0x35
void saload(MethodData *method_data);
// 0x36
void istore(MethodData *method_data);
// 0x37
void lstore(MethodData *method_data);
// 0x38
void fstore(MethodData *method_data);
// 0x39
void dstore(MethodData *method_data);
// 0x3A
void astore(MethodData *method_data);
// 0x3B
void istore_0(MethodData *method_data);
// 0x3C
void istore_1(MethodData *method_data);
// 0x3D
void istore_2(MethodData *method_data);
// 0x3E
void istore_3(MethodData *method_data);
// 0x3F
void lstore_0(MethodData *method_data);
// 0x40
void lstore_1(MethodData *method_data);
// 0x41
void lstore_2(MethodData *method_data);
// 0x42
void lstore_3(MethodData *method_data);
// 0x43
void fstore_0(MethodData *method_data);
// 0x44
void fstore_1(MethodData *method_data);
// 0x45
void fstore_2(MethodData *method_data);
// 0x46
void fstore_3(MethodData *method_data);
// 0x47
void dstore_0(MethodData *method_data);
// 0x48
void dstore_1(MethodData *method_data);
// 0x49
void dstore_2(MethodData *method_data);
// 0x4A
void dstore_3(MethodData *method_data);
// 0x4B
void astore_0(MethodData *method_data);
// 0x4C
void astore_1(MethodData *method_data);
// 0x4D
void astore_2(MethodData *method_data);
// 0x4E
void astore_3(MethodData *method_data);
// 0x4F
void iastore(MethodData *method_data);
// 0x50
void lastore(MethodData *method_data);
// 0x51
void fastore(MethodData *method_data);
// 0x52
void dastore(MethodData *method_data);
// 0x53
void aastore(MethodData *method_data);
// 0x54
void bastore(MethodData *method_data);
// 0x55
void castore(MethodData *method_data);
// 0x56
void sastore(MethodData *method_data);
// 0x57 (optional implementation?)
void pop(MethodData *method_data);
// 0x58 (optional implementation?)
void pop2(MethodData *method_data);
// 0x59 (optional implementation?)
void dup(MethodData *method_data);
// 0x5A (optional implementation?)
void dup_x1(MethodData *method_data);
// 0x5B (optional implementation?)
void dup_x2(MethodData *method_data);
// 0x5C (optional implementation?)
void dup2(MethodData *method_data);
// 0x5D (optional implementation?)
void dup2_x1(MethodData *method_data);
// 0x5E (optional implementation?)
void dup2_x2(MethodData *method_data);
// 0x5F (optional implementation?)
void swap(MethodData *method_data);
// 0x60
void iadd(MethodData *method_data);
// 0x61
void ladd(MethodData *method_data);
// 0x62
void fadd(MethodData *method_data);
// 0x63
void dadd(MethodData *method_data);
// 0x64
void isub(MethodData *method_data);
// 0x65
void lsub(MethodData *method_data);
// 0x66
void fsub(MethodData *method_data);
// 0x67
void dsub(MethodData *method_data);
// 0x68
void imul(MethodData *method_data);
// 0x69
void lmul(MethodData *method_data);
// 0x6A
void fmul(MethodData *method_data);
// 0x6B
void dmul(MethodData *method_data);
// 0x6C
void idiv(MethodData *method_data);
// 0x6D
void jvm_ldiv(MethodData *method_data);
// 0x6E
void fdiv(MethodData *method_data);
// 0x6F
void ddiv(MethodData *method_data);
// 0x70
void irem(MethodData *method_data);
// 0x71
void lrem(MethodData *method_data);
// 0x72
void frem(MethodData *method_data);
// 0x73
void drem(MethodData *method_data);
// 0x74
void ineg(MethodData *method_data);
// 0x75
void lneg(MethodData *method_data);
// 0x76
void fneg(MethodData *method_data);
// 0x77
void dneg(MethodData *method_data);
// 0x78
void ishl(MethodData *method_data);
// 0x79
void lshl(MethodData *method_data);
// 0x7A
void ishr(MethodData *method_data);
// 0x7B
void lshr(MethodData *method_data);
// 0x7C
void iushr(MethodData *method_data);
// 0x7D
void lushr(MethodData *method_data);
// 0x7E
void iand(MethodData *method_data);
// 0x7F
void land(MethodData *method_data);
// 0x80
void ior(MethodData *method_data);
// 0x81
void lor(MethodData *method_data);
// 0x82
void ixor(MethodData *method_data);
// 0x83
void lxor(MethodData *method_data);
// 0x84
void iinc(MethodData *method_data);
// 0x85
void i2l(MethodData *method_data);
// 0x86
void i2f(MethodData *method_data);
// 0x87
void i2d(MethodData *method_data);
// 0x88
void l2i(MethodData *method_data);
// 0x89
void l2f(MethodData *method_data);
// 0x8A
void l2d(MethodData *method_data);
// 0x8B
void f2i(MethodData *method_data);
// 0x8C
void f2l(MethodData *method_data);
// 0x8D
void f2d(MethodData *method_data);
// 0x8E
void d2i(MethodData *method_data);
// 0x8F
void d2l(MethodData *method_data);
// 0x90
void d2f(MethodData *method_data);
// 0x91
void i2b(MethodData *method_data);
// 0x92
void i2c(MethodData *method_data);
// 0x93
void i2s(MethodData *method_data);
// 0x94
void lcmp(MethodData *method_data);
// 0x95
void fcmpl(MethodData *method_data);
// 0x96
void fcmpg(MethodData *method_data);
// 0x97
void dcmpl(MethodData *method_data);
// 0x98
void dcmpg(MethodData *method_data);
// 0x99
void ifeq(MethodData *method_data);
// 0x9A
void ifne(MethodData *method_data);
// 0x9B
void iflt(MethodData *method_data);
// 0x9C
void ifge(MethodData *method_data);
// 0x9D
void ifgt(MethodData *method_data);
// 0x9E
void ifle(MethodData *method_data);
// 0x9F
void if_icmpeq(MethodData *method_data);
// 0xA0
void if_icmpne(MethodData *method_data);
// 0xA1
void if_icmplt(MethodData *method_data);
// 0xA2
void if_icmpge(MethodData *method_data);
// 0xA3
void if_icmpgt(MethodData *method_data);
// 0xA4
void if_icmple(MethodData *method_data);
// 0xA5
void if_acmpeg(MethodData *method_data);
// 0xA6
void if_acmpne(MethodData *method_data);
// 0xA7 ("goto" is a C keyword, hence the name)
void jvm_goto(MethodData *method_data);
// 0xA8
void jsr(MethodData *method_data);
// 0xA9
void ret(MethodData *method_data);
// 0xAA
void tableswitch(MethodData *method_data);
// 0xAB
void lookupswitch(MethodData *method_data);
// 0xAC
void ireturn(MethodData *method_data);
// 0xAD
void lreturn(MethodData *method_data);
// 0xAE
void freturn(MethodData *method_data);
// 0xAF
void dreturn(MethodData *method_data);
// 0xB0
void areturn(MethodData *method_data);
// 0xB1 ("return" is a C keyword, hence the name)
void jvm_return(MethodData *method_data);
// 0xB2
void getstatic(MethodData *method_data);
// 0xB3
void putstatic(MethodData *method_data);
// 0xB4
void getfield(MethodData *method_data);
// 0xB5
void putfield(MethodData *method_data);
// 0xB6
void invokevirtual(MethodData *method_data);
// 0xB7
void invokespecial(MethodData *method_data);
// 0xB8
void invokestatic(MethodData *method_data);
// 0xB9
void invokeinterface(MethodData *method_data);
// 0xBB (skipped 0xBA (186) - invokedynamic)
void new_func(MethodData *method_data);
// 0xBC
void newarray(MethodData *method_data);
// 0xBD
void anewarray(MethodData *method_data);
// 0xBE
void arraylength(MethodData *method_data);
// 0xBF (optional implementation?)
void athrow(MethodData *method_data);
// 0xC0 (optional implementation?)
void checkcast(MethodData *method_data);
// 0xC1 (optional implementation?)
void instanceof (MethodData * method_data);
// 0xC2 (optional implementation?)
void monitorenter(MethodData *method_data);
// 0xC3 (optional implementation?)
void monitorexit(MethodData *method_data);
// 0xC4
void wide(MethodData *method_data);
// 0xC5
void multianewarray(MethodData *method_data);
// 0xC6
void ifnull(MethodData *method_data);
// 0xC7
void ifnonnull(MethodData *method_data);
// 0xC8
void goto_w(MethodData *method_data);
// 0xC9
void jsr_w(MethodData *method_data);

#endif
