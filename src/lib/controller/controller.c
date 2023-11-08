#include <stdio.h>
#include <string.h>

#include "lib/base/class_file/class_defines.h"
#include "lib/base/class_file/class_file.h"
#include "lib/class_loader/bootstrap/bootstrap.h"
#include "lib/controller/controller.h"

// Function that parses the command line arguments.
// The program requires the user to pass two arguments:
//     - the execution mode ("-read" or "-run");
//     - the qualified name for the ".class" file.
int jvm_run(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("[JVM - ERROR] Missing Arguments\n");
        return -1;
    }

    if (!strcmp(argv[1], "-read"))
    {
        jvm_read_class(argv[2]);
    }
    else if (!strcmp(argv[1], "-run"))
    {
        jvm_run_class(argv[2]);
    }
    else
    {
        printf("[JVM - ERROR] Wrong Option");
        return -1;
    }

    return 0;
}

// Function that reads the bytecode of the ".class" file passed as an argument.
// The bytecode information is stored in a "class_file" struct, which is then printed on the standard output stream.
void jvm_read_class(char *class_file_path)
{
    ClassFile class_file = load_class_file(class_file_path);

    jvm_display_general_information(class_file);
    jvm_display_constant_pool(class_file.constant_pool, class_file.constant_pool_count);
    jvm_display_interfaces(class_file.interfaces_count, class_file.interfaces, class_file.constant_pool);
    jvm_display_fields(class_file.fields_count, class_file.fields, class_file.constant_pool);
    jvm_display_methods(class_file.methods_count, class_file.methods, class_file.constant_pool);
    jvm_display_attributes(class_file.attributes_count, class_file.attributes, class_file.constant_pool, 0);

    free_class_file(class_file);
}

void jvm_run_class(char *class_file_path)
{
    printf("[JVM ERROR] - Not Implemented yet\n");
    printf("Path: %s\n", class_file_path);
}

// Function that prints the general information of a ".class" file in the standard output stream.
void jvm_display_general_information(ClassFile class_file)
{
    printf("<General Information>\n");
    printf("   Minor Version: %d\n", class_file.minor_version);
    printf("   Major Version: %d\n", class_file.major_version);
    printf("   Constant Pool Count: %d\n", class_file.constant_pool_count);
    printf("   Access Flags: 0x%x\n", class_file.access_flags);

    u2 this_class_index = class_file.constant_pool[class_file.this_class - 1].info.Class.name_index;
    char this_class[200];
    get_utf8_value(this_class_index - 1, class_file.constant_pool, this_class);
    printf("   This Class: %d (%s)\n", this_class_index, this_class);

    printf("   Interfaces Count: %d\n", class_file.interfaces_count);
    printf("   Fields Count: %d\n", class_file.fields_count);
    printf("   Methods Count: %d\n", class_file.methods_count);
    printf("   Attributes Count: %d\n\n", class_file.attributes_count);
}

// Function that prints the constant pool elements of a ".class" file in the standard output stream.
void jvm_display_constant_pool(cp_info *constant_pool, u2 constant_pool_count)
{
    printf("<Constant Pool>\n");
    cp_info *constant_pool_element;
    u4 index = 0;
    for (constant_pool_element = constant_pool; constant_pool_element < constant_pool_count + constant_pool - 1;
         constant_pool_element++)
    {
        index += 1;
        printf("   [%d] Tag: %d (%s)\n", index, constant_pool_element->tag,
               get_cp_info_name(constant_pool_element->tag));

        switch (constant_pool_element->tag)
        {
        case CONSTANT_Class:
            printf("      Class Name: %d\n", constant_pool_element->info.Class.name_index);
            break;
        case CONSTANT_Fieldref:
            printf("      Class Name: %d\n", constant_pool_element->info.Fieldref.class_index);
            printf("      Name and Type: %d\n", constant_pool_element->info.Fieldref.name_and_type_index);
            break;
        case CONSTANT_Methodref:
            printf("      Class Name: %d\n", constant_pool_element->info.Methodref.class_index);
            printf("      Name and Type: %d\n", constant_pool_element->info.Methodref.name_and_type_index);
            break;
        case CONSTANT_InterfaceMethodref:
            printf("      Class Name: %d\n", constant_pool_element->info.InterfaceMethodref.class_index);
            printf("      Name and Type: %d\n", constant_pool_element->info.InterfaceMethodref.name_and_type_index);
            break;
        case CONSTANT_String:
            printf("      String Index: %d\n", constant_pool_element->info.String.string_index);
            break;
        case CONSTANT_Integer:
            printf("      Bytes: %u\n", constant_pool_element->info.Integer.bytes);
            break;
        case CONSTANT_Float:
            printf("      Bytes: %x\n", constant_pool_element->info.Float.bytes);
            break;
        case CONSTANT_Long:
            printf("      High Bytes: %x\n", constant_pool_element->info.Long.high_bytes);
            printf("      Low Bytes: %x\n", constant_pool_element->info.Long.low_bytes);
            break;
        case CONSTANT_Double:
            printf("      High Bytes: %x\n", constant_pool_element->info.Double.high_bytes);
            printf("      Low Bytes: %x\n", constant_pool_element->info.Double.low_bytes);
            break;
        case CONSTANT_NameAndType:
            printf("      Name Index: %d\n", constant_pool_element->info.NameAndType.name_index);
            printf("      Descriptor Index: %d\n", constant_pool_element->info.NameAndType.descriptor_index);
            break;
        case CONSTANT_Utf8: {
            printf("      Length of byte array: %d\n", constant_pool_element->info.Utf8.length);
            printf("      Length of byte string: %d\n", constant_pool_element->info.Utf8.length);

            char string[200];
            get_utf8_value(index - 1, constant_pool, string);
            printf("      String: %s\n", string);
            break;
        }
        }
    }
    printf("\n");
}

// Function that prints the details of the interfaces of a ".class" file in the standard output stream.
void jvm_display_interfaces(u2 interfaces_count, u2 *interfaces, cp_info *constant_pool)
{
    printf("<Interfaces>\n");
    if (interfaces_count == 0)
    {
        printf("   No Interfaces\n\n");
        return;
    }
    u2 *interface;
    for (interface = interfaces; interface < interfaces + interfaces_count; interface++)
    {
        u2 index = constant_pool[*interface - 1].info.Class.name_index;
        char interface_string[200];
        get_utf8_value(index - 1, constant_pool, interface_string);
        printf("   Interface: %d (%s)\n", *interface, interface_string);
    }
    printf("\n");
}

// Function that prints the details of the fields of a ".class" file in the standard output stream.
void jvm_display_fields(u2 fields_count, field_info *fields, cp_info *constant_pool)
{
    printf("<Fields>\n");
    if (fields_count == 0)
    {
        printf("   No Fields\n\n");
        return;
    }

    field_info *field;
    for (field = fields; field < fields + fields_count; field++)
    {
        char field_string[400];
        get_utf8_value(field->name_index - 1, constant_pool, field_string);
        printf("   Name: %d (%s)\n", field->name_index, field_string);

        get_utf8_value(field->descriptor_index - 1, constant_pool, field_string);
        printf("   Descriptor: %d (%s)\n", field->descriptor_index, field_string);

        printf("   Access Flags: 0x%x\n", field->access_flags);
        printf("   Attributes Count: %d\n\n", field->attributes_count);

        jvm_display_attributes(field->attributes_count, field->attributes, constant_pool, DEFAULT_SPACES);
    }
}

// Function that prints the details of the methods of a ".class" file in the standard output stream.
void jvm_display_methods(u2 methods_count, method_info *methods, cp_info *constant_pool)
{
    printf("<Methods>\n");
    method_info *method;
    for (method = methods; method < methods + methods_count; method++)
    {
        char method_string[400];
        get_utf8_value(method->name_index - 1, constant_pool, method_string);
        printf("   Name: %d (%s)\n", method->name_index, method_string);

        get_utf8_value(method->descriptor_index - 1, constant_pool, method_string);
        printf("   Descriptor: %d (%s)\n", method->descriptor_index, method_string);
        printf("   Access Flags: 0x%x\n", method->access_flags);
        printf("   Attributes Count: %d\n", method->attributes_count);
        jvm_display_attributes(method->attributes_count, method->attributes, constant_pool, DEFAULT_SPACES);
        printf("\n");
    }
}

// Function that prints the attributes of a ".class" file in the standard output stream.
void jvm_display_attributes(u2 attributes_count, attribute_info *attributes, cp_info *constant_pool, u4 spaces_count)
{
    jvm_print_spaces(spaces_count);
    printf("<Attributes>\n");
    if (attributes_count == 0)
    {
        jvm_print_spaces(spaces_count + DEFAULT_SPACES);
        printf("No Attributes\n");
        return;
    }

    attribute_info *attribute;
    for (attribute = attributes; attribute < attributes + attributes_count; attribute++)
    {
        char attribute_string[400];
        get_utf8_value(attribute->attribute_name_index - 1, constant_pool, attribute_string);

        jvm_print_spaces(spaces_count + DEFAULT_SPACES);
        printf("Attribute name index: %d (%s)\n", attribute->attribute_name_index, attribute_string);

        jvm_print_spaces(spaces_count + DEFAULT_SPACES);
        printf("Attribute length: %d\n", attribute->attribute_length);

        jvm_display_specific_attributes_info(attribute_string, attribute, constant_pool, spaces_count + DEFAULT_SPACES);
    }
}

// Auxiliary function for formatting purposes.
void jvm_print_spaces(u4 spaces_count)
{
    for (u4 i = 0; i < spaces_count; i++)
    {
        printf(" ");
    }
}

// Function that displays additional details of an attribute in the standard output stream.
void jvm_display_specific_attributes_info(const char *type, attribute_info *attribute, cp_info *constant_pool,
                                          u4 spaces_count)
{
    jvm_print_spaces(spaces_count);
    printf("<Specific Info - ");

    if (!strcmp(type, "ConstantValue"))
    {
        jvm_display_attrib_constant_value(attribute, constant_pool, spaces_count);
    }
    else if (!strcmp(type, "Code"))
    {
        jvm_display_attrib_code(attribute, constant_pool, spaces_count);
    }
    else if (!strcmp(type, "Exceptions"))
    {
        jvm_display_attrib_exceptions(attribute, constant_pool, spaces_count);
    }
    else if (!strcmp(type, "SourceFile"))
    {
        jvm_display_attrib_source_file(attribute, constant_pool, spaces_count);
    }
    else if (!strcmp(type, "Synthetic"))
    {
        jvm_display_attrib_synthetic(attribute, constant_pool, spaces_count);
    }
    else if (!strcmp(type, "InnerClasses")) // Adicione esta parte para InnerClasses
    {
        jvm_display_attrib_inner_classes(attribute, constant_pool, spaces_count);
    }
    else
    {
        printf("Undefined>\n");
    }
}

// Function for displaying code attribute.
void jvm_display_attrib_code(attribute_info *attribute, cp_info *constant_pool, u4 spaces_count)
{
    printf("Code>\n");

    jvm_print_spaces(spaces_count + DEFAULT_SPACES);
    printf("* Bytecode:\n");

    u1 *code;
    for (code = attribute->info.code.code; code < attribute->info.code.code + attribute->info.code.code_length; code++)
    {
        jvm_print_spaces(spaces_count + 2 * DEFAULT_SPACES);
        printf("0x%x\n", *code);
    }

    jvm_print_spaces(spaces_count + DEFAULT_SPACES);
    printf("* Exception Table:\n");
    if (attribute->info.code.exception_table_length == 0)
    {
        jvm_print_spaces(spaces_count + 2 * DEFAULT_SPACES);
        printf("No Exceptions\n");
    }
    else
    {
        jvm_print_spaces(spaces_count + 2 * DEFAULT_SPACES);
        printf("| Start PC |   End PC  | Handler PC | Catch Type |\n");
        Exception_table *exception_element;
        for (exception_element = attribute->info.code.exception_table;
             exception_element < attribute->info.code.exception_table + attribute->info.code.exception_table_length;
             exception_element++)
        {
            jvm_print_spaces(spaces_count + 2 * DEFAULT_SPACES);
            printf("|  %05d   |   %05d   |    %05d   |    %05d   |\n", exception_element->start_pc,
                   exception_element->end_pc, exception_element->handler_pc, exception_element->catch_type);
        }
    }

    jvm_print_spaces(spaces_count + DEFAULT_SPACES);
    printf("* Misc:\n");

    jvm_print_spaces(spaces_count + 2 * DEFAULT_SPACES);
    printf("Maximum Stack Size: %d\n", attribute->info.code.max_stack);
    jvm_print_spaces(spaces_count + 2 * DEFAULT_SPACES);
    printf("Maximum Local Variables: %d\n", attribute->info.code.max_locals);
    jvm_print_spaces(spaces_count + 2 * DEFAULT_SPACES);
    printf("Code Length: %d\n", attribute->info.code.code_length);

    jvm_display_attributes(attribute->info.code.attributes_count, attribute->info.code.attributes, constant_pool,
                           spaces_count + DEFAULT_SPACES);
}

// Function that prints the source file of the attribute in the standard output stream.
void jvm_display_attrib_source_file(attribute_info *attribute, cp_info *constant_pool, u4 spaces_count)
{
    char source_string[400];
    printf("Source File>\n");

    get_utf8_value(attribute->info.source_file.sourcefile_index - 1, constant_pool, source_string);
    jvm_print_spaces(spaces_count + DEFAULT_SPACES);

    printf("Source File Name Index: %d (%s)\n", attribute->info.source_file.sourcefile_index, source_string);
}

void jvm_display_attrib_constant_value(attribute_info *attribute, cp_info *constant_pool, u4 spaces_count)
{
    jvm_print_spaces(spaces_count + DEFAULT_SPACES);
    printf("ConstantValue>\n");

    jvm_print_spaces(spaces_count + 2 * DEFAULT_SPACES);
    printf("ConstantValue Index: %d\n", attribute->info.constant_value.constantvalue_index);
}

void jvm_display_attrib_exceptions(attribute_info *attribute, cp_info *constant_pool, u4 spaces_count)
{
    jvm_print_spaces(spaces_count + DEFAULT_SPACES);
    printf("Exceptions>\n");

    jvm_print_spaces(spaces_count + 2 * DEFAULT_SPACES);
    printf("Number of Exceptions: %d\n", attribute->info.exceptions.number_of_exceptions);

    if (attribute->info.exceptions.number_of_exceptions > 0)
    {
        jvm_print_spaces(spaces_count + 2 * DEFAULT_SPACES);
        printf("Exception Index Table:\n");

        u2 *exception_index_table = attribute->info.exceptions.exception_index_table;
        for (int i = 0; i < attribute->info.exceptions.number_of_exceptions; i++)
        {
            jvm_print_spaces(spaces_count + 3 * DEFAULT_SPACES);
            printf("[%d] Exception Index: %d\n", i, exception_index_table[i]);
        }
    }
}

void jvm_display_attrib_synthetic(attribute_info *attribute, cp_info *constant_pool, u4 spaces_count)
{
    jvm_print_spaces(spaces_count + DEFAULT_SPACES);
    printf("Synthetic>\n");

    jvm_print_spaces(spaces_count + 2 * DEFAULT_SPACES);
    printf("Attribute name index: %d\n", attribute->attribute_name_index);
    jvm_print_spaces(spaces_count + 2 * DEFAULT_SPACES);
    printf("Attribute length: %d\n", attribute->attribute_length);
}

void jvm_display_attrib_inner_classes(attribute_info *attribute, cp_info *constant_pool, u4 spaces_count)
{
    jvm_print_spaces(spaces_count + DEFAULT_SPACES);
    printf("InnerClasses>\n");

    InnerClasses_attribute inner_classes = attribute->info.inner_classes;

    jvm_print_spaces(spaces_count + 2 * DEFAULT_SPACES);
    printf("Number of Inner Classes: %d\n", inner_classes.number_of_classes);

    if (inner_classes.number_of_classes > 0)
    {
        jvm_print_spaces(spaces_count + 2 * DEFAULT_SPACES);
        printf("Inner Classes Information:\n");

        Classes *classes = inner_classes.classes;
        for (int i = 0; i < inner_classes.number_of_classes; i++)
        {
            jvm_print_spaces(spaces_count + 3 * DEFAULT_SPACES);
            printf("[%d] Inner Class Info Index: %d\n", i, classes[i].inner_class_info_index);

            jvm_print_spaces(spaces_count + 3 * DEFAULT_SPACES);
            printf("    Outer Class Info Index: %d\n", classes[i].outer_class_info_index);

            jvm_print_spaces(spaces_count + 3 * DEFAULT_SPACES);
            printf("    Inner Class Name Index: %d\n", classes[i].inner_name_index);

            jvm_print_spaces(spaces_count + 3 * DEFAULT_SPACES);
            printf("    Inner Class Access Flags: 0x%x\n", classes[i].inner_class_access_flags);
        }
    }
}
