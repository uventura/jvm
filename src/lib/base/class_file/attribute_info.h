#ifndef JVM_ATTRIBUTE_INFO
#define JVM_ATTRIBUTE_INFO

#include "lib/base/defines.h"

// Attribute Info
typedef struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u1 *info;
} attribute_info;

/*
Reference: https://docs.oracle.com/javase/specs/jvms/se8/html/jvms-4.html#jvms-4.7
    - ConstantValue
    - Code
    - Exceptions
    - SourceFile
    - LineNumberTable
    - LocalVariableTable
    - InnerClasses
    Synthetic
    Deprecated
    EnclosingMethod
    Signature
    SourceDebugExtension
    LocalVariableTypeTable
    RuntimeVisibleAnnotations
    RuntimeInvisibleAnnotations
    RuntimeVisibleParameterAnnotations
    RuntimeInvisibleParameterAnnotations
    AnnotationDefault
    - StackMapTable
    - BootstrapMethods
    RuntimeVisibleTypeAnnotations
    RuntimeInvisibleTypeAnnotations
    - MethodParameters
*/

// ConstantValue_attribute
typedef struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 constantvalue_index;
} ConstantValue_attribute;

// Code_attribute
typedef struct
{
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
} Exception_table;

typedef struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code;
    u2 exception_table_length;
    Exception_table exception_table;
    u2 attributes_count;
    attribute_info *attributes;
} Code_attribute;

// SourceFile_attribute
typedef struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 sourcefile_index;
} SourceFile_attribute;

// Exceptions_attribute
typedef struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_exceptions;
    u2 *exception_index_table;
} Exceptions_attribute;

// LineNumberTable_attribute
typedef struct
{
    u2 start_pc;
    u2 line_number;
} Line_number_table;

typedef struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 line_number_table_length;
    Line_number_table *line_number_table;
} LineNumberTable_attribute;

// LocalVariableTable_attribute
typedef struct
{
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
} Local_variable_table;

typedef struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 local_variable_table_length;
    Local_variable_table *local_variable_table;
} LocalVariableTable_attribute;

// InnerClasses_attribute
typedef struct
{
    u2 inner_class_info_index;
    u2 outer_class_info_index;
    u2 inner_name_index;
    u2 inner_class_access_flags;
} Classes;

typedef struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_classes;
    Classes *classes;
} InnerClasses_attribute;

// StackMapTable
typedef struct
{
    u1 tag;
} Top_variable_info;

typedef struct
{
    u1 tag; /* 1 */
} Integer_variable_info;

typedef struct
{
    u1 tag; /* 2 */
} Float_variable_info;

typedef struct
{
    u1 tag; /* 5 */
} Null_variable_info;

typedef struct
{
    u1 tag; /* 6 */
} UninitializedThis_variable_info;

typedef struct
{
    u1 tag; /* 7 */
    u2 cpool_index;
} Object_variable_info;

typedef struct Uninitialized_variable_info
{
    u1 tag; /* 8 */
    u2 offset;
} Uninitialized_variable_info;

typedef struct
{
    u1 tag; /* 4 */
} Long_variable_info;

typedef struct
{
    u1 tag; /* 3 */
} Double_variable_info;

typedef union {
    Top_variable_info top_variable_info;
    Integer_variable_info integer_variable_info;
    Float_variable_info float_variable_info;
    Long_variable_info long_variable_info;
    Double_variable_info double_variable_info;
    Null_variable_info null_variable_info;
    UninitializedThis_variable_info uninitializedThis_variable_info;
    Object_variable_info object_variable_info;
    Uninitialized_variable_info uninitialized_variable_info;
} verification_type_info;

typedef struct
{
    u1 frame_type;
} Same_frame;

typedef struct
{
    u1 frame_type;
    verification_type_info stack;
} Same_locals_1_stack_item_frame;

typedef struct
{
    u1 frame_type;
    u2 offset_delta;
    verification_type_info stack;
} Same_locals_1_stack_item_frame_extended;

typedef struct
{
    u1 frame_type;
    u2 offset_delta;
} Chop_frame;

typedef struct
{
    u1 frame_type;
    u2 offset_delta;
} Same_frame_extended;

typedef struct
{
    u1 frame_type;
    u2 offset_delta;
    verification_type_info *locals;
} Append_frame;

typedef struct
{
    u1 frame_type; /* 255 */
    u2 offset_delta;
    u2 number_of_locals;
    verification_type_info *locals;
    u2 number_of_stack_items;
    verification_type_info stack;
} Full_frame;

typedef union {
    Same_frame same_frame;
    Same_locals_1_stack_item_frame same_locals_1_stack_item_frame;
    Same_locals_1_stack_item_frame_extended same_locals_1_stack_item_frame_extended;
    Chop_frame chop_frame;
    Same_frame_extended same_frame_extended;
    Append_frame append_frame;
    Full_frame full_frame;
} stack_map_frame;

typedef struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_entries;
    stack_map_frame *entries;
} StackMapTable_attribute;

// BootstrapMethods
typedef struct
{
    u2 bootstrap_method_ref;
    u2 num_bootstrap_arguments;
    u2 *bootstrap_arguments;
} Bootstrap_methods;

typedef struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 num_bootstrap_methods;
    Bootstrap_methods *bootstrap_methods;
} BootstrapMethods_attribute;

// MethodParameters
typedef struct
{
    u2 name_index;
    u2 access_flags;
} Parameters;

typedef struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u1 parameters_count;
    Parameters *parameters;
} MethodParameters_attribute;

#endif
