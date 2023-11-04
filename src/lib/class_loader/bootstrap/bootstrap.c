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
    class_file.fields = load_field_info(class_file_element, class_file.fields_count);
    class_file.methods_count = u2_read(class_file_element);
    class_file.methods = load_method_info(class_file_element, class_file.methods_count);
    class_file.attributes_count = u2_read(class_file_element);
    class_file.attributes = load_attribute_info(class_file_element, class_file.attributes_count);

    fclose(class_file_element);

    return class_file;
}

void free_class_file(ClassFile class_file)
{
    free_constant_pool(class_file.constant_pool_count, class_file.constant_pool);
    free_interfaces(class_file.interfaces);
    free_fields(class_file.fields_count, class_file.fields);
    free_methods(class_file.methods_count, class_file.methods);
    free_attributes(class_file.attributes_count, class_file.attributes);
}

// Constant Pool
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
            fread((void *)&(constant_pool_element->info.Class), sizeof(CONSTANT_Class_info), 1, file);
            break;
        case CONSTANT_Fieldref:
            fread((void *)&(constant_pool_element->info.Fieldref), sizeof(CONSTANT_Fieldref_info), 1, file);
            break;
        case CONSTANT_Methodref:
            fread((void *)&(constant_pool_element->info.Methodref), sizeof(CONSTANT_Methodref_info), 1, file);
            break;
        case CONSTANT_InterfaceMethodref:
            fread((void *)&(constant_pool_element->info.InterfaceMethodref), sizeof(CONSTANT_InterfaceMethodref_info),
                  1, file);
            break;
        case CONSTANT_String:
            fread((void *)&(constant_pool_element->info.String), sizeof(CONSTANT_String_info), 1, file);
            break;
        case CONSTANT_Integer:
            fread((void *)&(constant_pool_element->info.Integer), sizeof(CONSTANT_Integer_info), 1, file);
            break;
        case CONSTANT_Float:
            fread((void *)&(constant_pool_element->info.Float), sizeof(CONSTANT_Float_info), 1, file);
            break;
        case CONSTANT_Long:
            fread((void *)&(constant_pool_element->info.Long), sizeof(CONSTANT_Long_info), 1, file);
            break;
        case CONSTANT_Double:
            fread((void *)&(constant_pool_element->info.Double), sizeof(CONSTANT_Double_info), 1, file);
            break;
        case CONSTANT_NameAndType:
            fread((void *)&(constant_pool_element->info.NameAndType), sizeof(CONSTANT_NameAndType_info), 1, file);
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
        }
    }

    return constant_pool;
}

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

void free_interfaces(u2 *interfaces)
{
    free(interfaces);
}

// Fields
field_info *load_field_info(FILE *file, u2 fields_count)
{
    field_info *fields = (field_info *)malloc(sizeof(field_info) * fields_count);
    field_info *field;
    for (field = fields; field < fields + fields_count; field++)
    {
        field->access_flags = u2_read(file);
        field->name_index = u2_read(file);
        field->descriptor_index = u2_read(file);
        field->attributes_count = u2_read(file);
        field->attributes = load_attribute_info(file, field->attributes_count);
    }

    return fields;
}

void free_fields(u2 field_count, field_info *fields)
{
    field_info *field;
    for (field = fields; field < fields + field_count; field++)
    {
        // This function is creating leaking
        // free_attributes(field->attributes_count, field->attributes);
        attribute_info *attribute;
        for (attribute = field->attributes; attribute < field->attributes + field->attributes_count; attribute++)
        {
            free(attribute->info);
        }
        free(field->attributes);
    }
    free(fields);
}

// Methods
method_info *load_method_info(FILE *file, u2 method_count)
{
    method_info *methods = (method_info *)malloc(sizeof(method_info) * method_count);
    method_info *method;
    for (method = methods; method < methods + method_count; method++)
    {
        method->access_flags = u2_read(file);
        method->name_index = u2_read(file);
        method->descriptor_index = u2_read(file);
        method->attributes_count = u2_read(file);
        method->attributes = load_attribute_info(file, method->attributes_count);
    }

    return methods;
}

void free_methods(u2 methods_count, method_info *methods)
{
    method_info *method;
    for (method = methods; method < methods + methods_count; method++)
    {
        attribute_info *attribute;
        for (attribute = method->attributes; attribute < method->attributes + method->attributes_count; attribute++)
        {
            free(attribute->info);
        }
        free(method->attributes);
    }
    free(methods);
}

// Attributes
attribute_info *load_attribute_info(FILE *file, u2 attributes_count)
{
    attribute_info *attributes = (attribute_info *)malloc(sizeof(attribute_info) * attributes_count);
    attribute_info *attribute;
    for (attribute = attributes; attribute < attributes + attributes_count; attribute++)
    {
        attribute->attribute_name_index = u2_read(file);
        attribute->attribute_length = u4_read(file);
        attribute->info = (u1 *)malloc(sizeof(u1) * attribute->attribute_length);

        u1 *info;
        for (info = attribute->info; info < attribute->info + attribute->attribute_length; info++)
        {
            *info = u1_read(file);
        }
    }

    return attributes;
}

void free_attributes(u2 attributes_count, attribute_info *attributes)
{
    if (attributes_count == 0)
    {
        return;
    }

    attribute_info *attribute;
    for (attribute = attributes; attribute < attributes + attributes_count; attribute++)
    {
        free(attribute->info);
    }
    free(attributes);
}
