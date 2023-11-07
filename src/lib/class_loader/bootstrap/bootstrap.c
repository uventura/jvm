#include "lib/class_loader/bootstrap/bootstrap.h"
#include "lib/base/class_file/attribute_info.h"
#include "lib/base/class_file/class_defines.h"
#include "lib/base/class_file/class_file.h"
#include "lib/base/class_file/cp_info.h"
#include "lib/base/class_file/field_info.h"
#include "lib/base/class_file/method_info.h"
#include "lib/base/file/read_bytes.h"

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Class File
// Opens the ".class" file for reading, checking for faults in the process.
// Creates a "class_file" struct to store the elements read from the bytecode, closes the file and returns the struct.
ClassFile load_class_file(const char *filepath)
{
    FILE *class_file_element = fopen(filepath, "rb");

    if (!class_file_element)
    {
        printf("[Class Loader - Bootstrap](ERROR) Couldn't open file...\n");
        exit(-1);
    }

    u4 cafe_babe = u4_read(class_file_element);
    if (cafe_babe != 0xCAFEBABE)
    {
        printf("[Class Loader - Bootstrap](ERROR) This is not a .class file...\n");
        exit(-1);
    }

    ClassFile class_file;
    class_file.magic = cafe_babe;
    class_file.minor_version = u2_read(class_file_element);
    class_file.major_version = u2_read(class_file_element);
    class_file.constant_pool_count = u2_read(class_file_element);
    class_file.constant_pool = load_constant_pool(class_file_element, class_file.constant_pool_count);
    class_file.access_flags = u2_read(class_file_element);
    class_file.this_class = u2_read(class_file_element);
    class_file.super_class = u2_read(class_file_element);
    class_file.interfaces_count = u2_read(class_file_element);
    class_file.interfaces = load_interfaces(class_file_element, class_file.interfaces_count);
    class_file.fields_count = u2_read(class_file_element);
    class_file.fields = load_field_info(class_file_element, class_file.fields_count, class_file.constant_pool);
    class_file.methods_count = u2_read(class_file_element);
    class_file.methods = load_method_info(class_file_element, class_file.methods_count, class_file.constant_pool);
    class_file.attributes_count = u2_read(class_file_element);
    class_file.attributes =
        load_attribute_info(class_file_element, class_file.attributes_count, class_file.constant_pool);

    fclose(class_file_element);

    return class_file;
}

// Function to free the memory allocated to the "class_file" struct.
void free_class_file(ClassFile class_file)
{
    free_interfaces(class_file.interfaces);
    free_fields(class_file.fields_count, class_file.fields, class_file.constant_pool);
    free_methods(class_file.methods_count, class_file.methods, class_file.constant_pool);
    free_attributes(class_file.attributes_count, class_file.attributes, class_file.constant_pool);
    free_constant_pool(class_file.constant_pool_count, class_file.constant_pool);
}

// Constant Pool
// Reads the bytecode of the "constant_pool", saving the data in a "cp_info" struct that is returned to the caller.
// In order to read each element correctly, their corresponding types (tags) are determined beforehand.
cp_info *load_constant_pool(FILE *file, u2 constant_pool_count)
{
    cp_info *constant_pool = (cp_info *)malloc(sizeof(cp_info) * constant_pool_count);
    cp_info *constant_pool_element;
    for (constant_pool_element = constant_pool; constant_pool_element < constant_pool + constant_pool_count - 1;
         constant_pool_element++)
    {
        constant_pool_element->tag = u1_read(file);
        switch (constant_pool_element->tag)
        {
        case CONSTANT_Class:
            constant_pool_element->info.Class.name_index = u2_read(file);
            break;
        case CONSTANT_Fieldref:
            constant_pool_element->info.Fieldref.class_index = u2_read(file);
            constant_pool_element->info.Fieldref.name_and_type_index = u2_read(file);
            break;
        case CONSTANT_Methodref:
            constant_pool_element->info.Methodref.class_index = u2_read(file);
            constant_pool_element->info.Methodref.name_and_type_index = u2_read(file);
            break;
        case CONSTANT_InterfaceMethodref:
            constant_pool_element->info.InterfaceMethodref.class_index = u2_read(file);
            constant_pool_element->info.InterfaceMethodref.name_and_type_index = u2_read(file);
            break;
        case CONSTANT_String:
            constant_pool_element->info.String.string_index = u2_read(file);
            break;
        case CONSTANT_Integer:
            constant_pool_element->info.Integer.bytes = u4_read(file);
            break;
        case CONSTANT_Float:
            constant_pool_element->info.Float.bytes = u4_read(file);
            break;
        case CONSTANT_Long:
            constant_pool_element->info.Long.high_bytes = u4_read(file);
            constant_pool_element->info.Long.low_bytes = u4_read(file);
            break;
        case CONSTANT_Double:
            constant_pool_element->info.Double.high_bytes = u4_read(file);
            constant_pool_element->info.Double.low_bytes = u4_read(file);
            break;
        case CONSTANT_NameAndType:
            constant_pool_element->info.NameAndType.name_index = u2_read(file);
            constant_pool_element->info.NameAndType.descriptor_index = u2_read(file);
            break;
        case CONSTANT_Utf8: {
            u2 length = u2_read(file);
            u1 *byte_ref = (u1 *)malloc(length + 2);
            u1 *byte;
            for (byte = byte_ref; byte < byte_ref + length; byte++)
                *byte = u1_read(file);

            constant_pool_element->info.Utf8.length = length;
            constant_pool_element->info.Utf8.bytes = byte_ref;
            break;
        }
        case CONSTANT_MethodHandle:
            constant_pool_element->info.MethodHandle.reference_kind = u2_read(file);
            constant_pool_element->info.MethodHandle.reference_index = u2_read(file);
            break;
        case CONSTANT_InvokeDynamic:
            constant_pool_element->info.InvokeDynamic.bootstrap_method_attr_index = u2_read(file);
            constant_pool_element->info.InvokeDynamic.name_and_type_index = u2_read(file);
            break;
        }
    }

    return constant_pool;
}

// Function to free the memory allocated to a "cp_info" struct.
void free_constant_pool(u2 constant_pool_count, cp_info *constant_pool)
{
    for (int i = 0; i < constant_pool_count; ++i)
    {
        const char *tag = get_cp_info_name(constant_pool[i].tag);
        if (strcmp(tag, "Utf8") == 0)
        {
            free(constant_pool[i].info.Utf8.bytes);
        }
    }
    free(constant_pool);
}

// Interfaces
// Reads the bytecode relative to the interfaces of the ".class" file.
u2 *load_interfaces(FILE *file, u2 interfaces_count)
{
    u2 *interfaces = (u2 *)malloc(sizeof(u2) * interfaces_count);
    u2 *interface;
    for (interface = interfaces; interface < interfaces + interfaces_count; interface++)
    {
        *interface = u2_read(file);
    }

    return interfaces;
}

// Function to free the memory allocated to a interface.
void free_interfaces(u2 *interfaces)
{
    free(interfaces);
}

// Fields
// Reads the bytecode corresponding to the fields, saving the data in a "field_info" struct that is returned.
field_info *load_field_info(FILE *file, u2 fields_count, cp_info *constant_pool)
{
    field_info *fields = (field_info *)malloc(sizeof(field_info) * fields_count);
    field_info *field;
    for (field = fields; field < fields + fields_count; field++)
    {
        field->access_flags = u2_read(file);
        field->name_index = u2_read(file);
        field->descriptor_index = u2_read(file);
        field->attributes_count = u2_read(file);
        field->attributes = load_attribute_info(file, field->attributes_count, constant_pool);
    }

    return fields;
}

// Function to free the memory allocated to a "field_info" struct.
void free_fields(u2 field_count, field_info *fields, cp_info *constant_pool)
{
    field_info *field;
    for (field = fields; field < fields + field_count; field++)
    {
        free_attributes(field->attributes_count, field->attributes, constant_pool);
        // TODO: Why do we need this second free?
        free(field->attributes);
    }
    free(fields);
}

// Methods
// Reads the bytecode of the methods, stores the data in a "method_info" struct that is returned.
method_info *load_method_info(FILE *file, u2 method_count, cp_info *constant_pool)
{
    method_info *methods = (method_info *)malloc(sizeof(method_info) * method_count);
    method_info *method;
    for (method = methods; method < methods + method_count; method++)
    {
        method->access_flags = u2_read(file);
        method->name_index = u2_read(file);
        method->descriptor_index = u2_read(file);
        method->attributes_count = u2_read(file);
        method->attributes = load_attribute_info(file, method->attributes_count, constant_pool);
    }

    return methods;
}

// Function to free the memory allocated to a "method_info" struct.
void free_methods(u2 methods_count, method_info *methods, cp_info *constant_pool)
{
    method_info *method;
    for (method = methods; method < methods + methods_count; method++)
    {
        free_attributes(method->attributes_count, method->attributes, constant_pool);
    }
    free(methods);
}

// Attributes
// Reads the bytecode relative to the attributes, storing the date in a "attribute_info" struct that is returned.
attribute_info *load_attribute_info(FILE *file, u2 attributes_count, cp_info *constant_pool)
{
    if (attributes_count == 0)
    {
        return NULL;
    }

    attribute_info *attributes = (attribute_info *)malloc((sizeof(attribute_info) * attributes_count));
    attribute_info *attribute;
    for (attribute = attributes; attribute < attributes + attributes_count; attribute++)
    {
        attribute->attribute_name_index = u2_read(file);
        attribute->attribute_length = u4_read(file);

        char type[100];
        memcpy(type, constant_pool[attribute->attribute_name_index - 1].info.Utf8.bytes,
               constant_pool[attribute->attribute_name_index - 1].info.Utf8.length);
        type[constant_pool[attribute->attribute_name_index - 1].info.Utf8.length] = '\0';

        attribute->info = load_attribute_type(file, type, constant_pool);
    }

    return attributes;
}

// Auxiliary function utilized to determine the type of the attribute and read it correctly.
attributes_type_info load_attribute_type(FILE *file, const char *type, cp_info *constant_pool)
{
    attributes_type_info attribute;
    if (!strcmp(type, "ConstantValue"))
    {
        attribute.constant_value.constantvalue_index = u2_read(file);
    }
    else if (!strcmp(type, "Code"))
    {
        attribute.code.max_stack = u2_read(file);
        attribute.code.max_locals = u2_read(file);
        attribute.code.code_length = u4_read(file);
        attribute.code.code = (u1 *)malloc(sizeof(u1) * attribute.code.code_length);
        u1 *code;
        for (code = attribute.code.code; code < attribute.code.code + attribute.code.code_length; code++)
        {
            *code = u1_read(file);
        }
        attribute.code.exception_table_length = u2_read(file);
        attribute.code.exception_table =
            (Exception_table *)malloc(sizeof(Exception_table) * attribute.code.exception_table_length);
        Exception_table *exception_table;
        for (exception_table = attribute.code.exception_table;
             exception_table < attribute.code.exception_table + attribute.code.exception_table_length;
             exception_table++)
        {
            exception_table->start_pc = u2_read(file);
            exception_table->end_pc = u2_read(file);
            exception_table->handler_pc = u2_read(file);
            exception_table->catch_type = u2_read(file);
        }
        attribute.code.attributes_count = u2_read(file);
        attribute.code.attributes = load_attribute_info(file, attribute.code.attributes_count, constant_pool);
    }
    else if (!strcmp(type, "Exceptions"))
    {
        attribute.exceptions.number_of_exceptions = u2_read(file);
        attribute.exceptions.exception_index_table =
            (u2 *)malloc(sizeof(u2) * attribute.exceptions.number_of_exceptions);
        u2 *index;
        for (index = attribute.exceptions.exception_index_table;
             index < attribute.exceptions.exception_index_table + attribute.exceptions.number_of_exceptions; index++)
        {
            *index = u2_read(file);
        }
    }
    else if (!strcmp(type, "InnerClasses"))
    {
        attribute.inner_classes.number_of_classes = u2_read(file);
        attribute.inner_classes.classes =
            (Classes *)malloc(sizeof(Classes) * attribute.inner_classes.number_of_classes);
        Classes *classes;
        for (classes = attribute.inner_classes.classes;
             classes < attribute.inner_classes.classes + attribute.inner_classes.number_of_classes; classes++)
        {
            classes->inner_class_info_index = u2_read(file);
            classes->outer_class_info_index = u2_read(file);
            classes->inner_name_index = u2_read(file);
            classes->inner_class_access_flags = u2_read(file);
        }
    }
    else if (!strcmp(type, "SourceFile"))
    {
        attribute.source_file.sourcefile_index = u2_read(file);
    }
    else if (!strcmp(type, "LineNumberTable"))
    {
        attribute.line_number_table.line_number_table_length = u2_read(file);
        attribute.line_number_table.line_number_table = (Line_number_table *)malloc(
            sizeof(Line_number_table) * attribute.line_number_table.line_number_table_length);
        Line_number_table *line_number_table;
        for (line_number_table = attribute.line_number_table.line_number_table;
             line_number_table <
             attribute.line_number_table.line_number_table + attribute.line_number_table.line_number_table_length;
             line_number_table++)
        {
            line_number_table->start_pc = u2_read(file);
            line_number_table->line_number = u2_read(file);
        };
    }
    else if (!strcmp(type, "LocalVariableTable"))
    {
        attribute.local_variable_table.local_variable_table_length = u2_read(file);
        attribute.local_variable_table.local_variable_table = (Local_variable_table *)malloc(
            sizeof(Local_variable_table) * attribute.local_variable_table.local_variable_table_length);
        Local_variable_table *local_variable_table;
        for (local_variable_table = attribute.local_variable_table.local_variable_table;
             local_variable_table < attribute.local_variable_table.local_variable_table +
                                        attribute.local_variable_table.local_variable_table_length;
             local_variable_table++)
        {
            local_variable_table->start_pc = u2_read(file);
            local_variable_table->length = u2_read(file);
            local_variable_table->name_index = u2_read(file);
            local_variable_table->descriptor_index = u2_read(file);
            local_variable_table->index = u2_read(file);
        }
    }
    else if (!strcmp(type, "Synthetic"))
    {
        // Does Nothing
    }
    return attribute;
}

// Function to free the memory allocated to a "attribute_info" struct.
void free_attributes(u2 attributes_count, attribute_info *attributes, cp_info *constant_pool)
{
    if (attributes_count == 0)
    {
        return;
    }

    attribute_info *attribute;
    for (attribute = attributes; attribute < attributes + attributes_count; attribute++)
    {
        char type[100];
        memcpy(type, constant_pool[attribute->attribute_name_index - 1].info.Utf8.bytes,
               constant_pool[attribute->attribute_name_index - 1].info.Utf8.length);
        type[constant_pool[attribute->attribute_name_index - 1].info.Utf8.length] = '\0';

        if (!strcmp(type, "Code"))
        {
            free(attribute->info.code.code);
            free_attributes(attribute->info.code.attributes_count, attribute->info.code.attributes, constant_pool);
            free(attribute->info.code.exception_table);
        }
        else if (!strcmp(type, "Exceptions"))
        {
            free(attribute->info.exceptions.exception_index_table);
        }
        else if (!strcmp(type, "InnerClasses"))
        {
            free(attribute->info.inner_classes.classes);
        }
        else if (!strcmp(type, "LineNumberTable"))
        {
            free(attribute->info.local_variable_table.local_variable_table);
        }
    }
    free(attributes);
}
