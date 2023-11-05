#ifndef JVM_ATTRIBUTE_INFO
#define JVM_ATTRIBUTE_INFO

#include "lib/base/defines.h"

// Attribute Info
typedef struct Attribute_info attribute_info;

/*
Reference: https://docs.oracle.com/javase/specs/jvms/se8/html/jvms-4.html#jvms-4.7
    - ConstantValue
    - Code
    - Exceptions
    - InnerClasses
    - LineNumberTable
    - LocalVariableTable
    - SourceFile
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
    StackMapTable
    - BootstrapMethods
    RuntimeVisibleTypeAnnotations
    RuntimeInvisibleTypeAnnotations
    - MethodParameters
*/

// ConstantValue_attribute
typedef struct
{
    // u2 attribute_name_index;
    // u4 attribute_length;
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
    // u2 attribute_name_index;
    // u4 attribute_length;
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code;
    u2 exception_table_length;
    Exception_table *exception_table;
    u2 attributes_count;
    attribute_info *attributes;
} Code_attribute;

// SourceFile_attribute
typedef struct
{
    // u2 attribute_name_index;
    // u4 attribute_length;
    u2 sourcefile_index;
} SourceFile_attribute;

// Exceptions_attribute
typedef struct
{
    // u2 attribute_name_index;
    // u4 attribute_length;
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
    // u2 attribute_name_index;
    // u4 attribute_length;
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
    // u2 attribute_name_index;
    // u4 attribute_length;
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
    // u2 attribute_name_index;
    // u4 attribute_length;
    u2 number_of_classes;
    Classes *classes;
} InnerClasses_attribute;

// Synthetic
typedef struct
{
    u2 attribute_name_index;
    u4 attribute_length;
} Synthetic_attribute;

// BootstrapMethods
typedef struct
{
    u2 bootstrap_method_ref;
    u2 num_bootstrap_arguments;
    u2 *bootstrap_arguments;
} Bootstrap_methods;

typedef struct
{
    // u2 attribute_name_index;
    // u4 attribute_length;
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
    // u2 attribute_name_index;
    // u4 attribute_length;
    u1 parameters_count;
    Parameters *parameters;
} MethodParameters_attribute;

// Attribute Info
typedef union {
    ConstantValue_attribute constant_value;
    Code_attribute code;
    Exceptions_attribute exceptions;
    InnerClasses_attribute inner_classes;
    SourceFile_attribute source_file;
    LineNumberTable_attribute line_number_table;
    LocalVariableTable_attribute local_variable_table;
    Synthetic_attribute synthetic;
} attributes_type_info;

struct Attribute_info
{
    u2 attribute_name_index;
    u4 attribute_length;
    attributes_type_info info;
};

#endif
