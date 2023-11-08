#include "unity/unity.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/class_loader/bootstrap/bootstrap.h"

void test_bootstrap_get_cafe_babe(void)
{
    ClassFile class_file = load_class_file("data/examples/HelloWorld.class");
    TEST_ASSERT_EQUAL(class_file.magic, 0XCAFEBABE);
    free_class_file(class_file);
}

void test_bootstrap_get_utf8_field(void)
{
    ClassFile class_file = load_class_file("data/examples/HelloWorld.class");

    char element[100];
    memcpy(element, class_file.constant_pool[11].info.Utf8.bytes, class_file.constant_pool[11].info.Utf8.length);
    element[class_file.constant_pool[11].info.Utf8.length] = '\0';

    TEST_ASSERT_EQUAL(0, strcmp(element, "([Ljava/lang/String;)V"));

    free_class_file(class_file);
}

// TESTING GENERAL INFORMATIONS OF .CLASS SOMA (interface)

void test_bootstrap_get_cafe_babe_soma(void)
{
    ClassFile class_file = load_class_file("data/examples/Soma.class");
    TEST_ASSERT_EQUAL(class_file.magic, 0XCAFEBABE);
    free_class_file(class_file);
}

void test_bootstrap_constant_pool_count_soma(void)
{

    ClassFile class_file = load_class_file("data/examples/Soma.class");
    u2 nine = 9;
    TEST_ASSERT_EQUAL(nine, class_file.constant_pool_count);
    free_class_file(class_file);
}

void test_bootstrap_access_flags_soma(void)
{
    ClassFile class_file = load_class_file("data/examples/Soma.class");
    TEST_ASSERT_EQUAL(0x0600, class_file.access_flags);
    free_class_file(class_file);
}

void test_bootstrap_interfaces_count_soma(void)
{

    ClassFile class_file = load_class_file("data/examples/Soma.class");
    TEST_ASSERT_EQUAL(0, class_file.interfaces_count);
    free_class_file(class_file);
}

void test_bootstrap_fields_count_soma(void)
{

    ClassFile class_file = load_class_file("data/examples/Soma.class");
    TEST_ASSERT_EQUAL(0, class_file.fields_count);
    free_class_file(class_file);
}

void test_bootstrap_methods_count_soma(void)
{

    ClassFile class_file = load_class_file("data/examples/Soma.class");
    TEST_ASSERT_EQUAL(1, class_file.methods_count);
    free_class_file(class_file);
}

void test_bootstrap_attributes_count_soma(void)
{

    ClassFile class_file = load_class_file("data/examples/Soma.class");
    TEST_ASSERT_EQUAL(1, class_file.attributes_count);
    free_class_file(class_file);
}

// TESTING GENERAL INFORMATIONS OF .CLASS MATEMATICO

void test_bootstrap_get_cafe_babe_matematico(void)
{
    ClassFile class_file = load_class_file("data/examples/Matematico.class");
    TEST_ASSERT_EQUAL(class_file.magic, 0XCAFEBABE);
    free_class_file(class_file);
}

void test_bootstrap_constant_pool_count_matematico(void)
{

    ClassFile class_file = load_class_file("data/examples/Matematico.class");
    TEST_ASSERT_EQUAL(48, class_file.constant_pool_count);
    free_class_file(class_file);
}

void test_bootstrap_access_flags_matematico(void)
{
    ClassFile class_file = load_class_file("data/examples/Matematico.class");
    TEST_ASSERT_EQUAL(0x0020, class_file.access_flags);
    free_class_file(class_file);
}

void test_bootstrap_interfaces_count_matematico(void)
{

    ClassFile class_file = load_class_file("data/examples/Matematico.class");
    TEST_ASSERT_EQUAL(1, class_file.interfaces_count);
    free_class_file(class_file);
}

void test_bootstrap_fields_count_matematico(void)
{

    ClassFile class_file = load_class_file("data/examples/Matematico.class");
    TEST_ASSERT_EQUAL(0, class_file.fields_count);
    free_class_file(class_file);
}

void test_bootstrap_methods_count_matematico(void)
{

    ClassFile class_file = load_class_file("data/examples/Matematico.class");
    TEST_ASSERT_EQUAL(2, class_file.methods_count);
    free_class_file(class_file);
}

void test_bootstrap_attributes_count_matematico(void)
{

    ClassFile class_file = load_class_file("data/examples/Matematico.class");
    TEST_ASSERT_EQUAL(3, class_file.attributes_count);
    free_class_file(class_file);
}

// TESTING GENERAL INFORMATION OF .CLASS CARRO

void test_bootstrap_get_cafe_babe_carro(void)
{
    ClassFile class_file = load_class_file("data/examples/Carro.class");
    TEST_ASSERT_EQUAL(class_file.magic, 0XCAFEBABE);
    free_class_file(class_file);
}

void test_bootstrap_constant_pool_count_carro(void)
{

    ClassFile class_file = load_class_file("data/examples/Carro.class");
    TEST_ASSERT_EQUAL(25, class_file.constant_pool_count);
    free_class_file(class_file);
}

void test_bootstrap_access_flags_carro(void)
{
    ClassFile class_file = load_class_file("data/examples/Carro.class");
    TEST_ASSERT_EQUAL(0x0020, class_file.access_flags);
    free_class_file(class_file);
}

void test_bootstrap_interfaces_count_carro(void)
{

    ClassFile class_file = load_class_file("data/examples/Carro.class");
    TEST_ASSERT_EQUAL(0, class_file.interfaces_count);
    free_class_file(class_file);
}

void test_bootstrap_fields_count_carro(void)
{

    ClassFile class_file = load_class_file("data/examples/Carro.class");
    TEST_ASSERT_EQUAL(1, class_file.fields_count);
    free_class_file(class_file);
}

void test_bootstrap_methods_count_carro(void)
{

    ClassFile class_file = load_class_file("data/examples/Carro.class");
    TEST_ASSERT_EQUAL(2, class_file.methods_count);
    free_class_file(class_file);
}

void test_bootstrap_attributes_count_carro(void)
{

    ClassFile class_file = load_class_file("data/examples/Carro.class");
    TEST_ASSERT_EQUAL(1, class_file.attributes_count);
    free_class_file(class_file);
}

/*

SÓ PRA ME ORIENTAR AQUI, OK?

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
*/