// Test library
#include "lib/controller/jvm_reader.h"
#include "unity/unity.h"
#include <stdio.h>
#include <string.h>

// Header from `src` directory
#include "lib/base/class_file/class_defines.h"
#include "lib/base/class_file/cp_info.h"
#include "lib/class_loader/bootstrap/bootstrap.h"
#include "lib/class_loader/class_file_list.h"

void test_class_file_list_initialization(void)
{
    ClassFileList cfl = class_file_list_init();
    TEST_ASSERT_EQUAL(cfl.num_elements, 0);
}

void test_class_file_list_loading_single_class(void)
{
    ClassFileList cfl = class_file_list_init();
    ClassFile class_file = load_class_file("data/examples/HelloWorld.class");
    class_file_list_insert(&cfl, &class_file, "HelloWorld");

    TEST_ASSERT_EQUAL(cfl.num_elements, 1);
    TEST_ASSERT_EQUAL(strcmp(cfl.head->class_name, "HelloWorld"), 0);

    u2 class_index = cfl.head->class->constant_pool[cfl.head->class->this_class - 1].info.Class.name_index;
    char name[100];
    get_utf8_value(class_index - 1, cfl.head->class->constant_pool, name);

    TEST_ASSERT_EQUAL(strcmp(name, "HelloWorld"), 0);

    class_file_list_free(&cfl);
}

void test_class_file_list_double_insert(void)
{
    ClassFileList cfl = class_file_list_init();
    ClassFile class_file = load_class_file("data/examples/HelloWorld.class");
    class_file_list_insert(&cfl, &class_file, "HelloWorld");
    class_file_list_insert(&cfl, &class_file, "HelloWorld");

    TEST_ASSERT_EQUAL(1, cfl.num_elements);

    class_file_list_free(&cfl);
}

void test_class_file_list_two_classes(void)
{
    ClassFileList cfl = class_file_list_init();
    ClassFile class_file_one = load_class_file("data/examples/HelloWorld.class");
    ClassFile class_file_two = load_class_file("data/examples/Carro.class");
    class_file_list_insert(&cfl, &class_file_one, "HelloWorld");
    class_file_list_insert(&cfl, &class_file_two, "Carro");

    TEST_ASSERT_EQUAL(2, cfl.num_elements);
    TEST_ASSERT_EQUAL(strcmp(cfl.head->class_name, "HelloWorld"), 0);
    TEST_ASSERT_EQUAL(strcmp(cfl.head->next->class_name, "Carro"), 0);

    ClassFileElement *element = cfl.head->next;
    u2 class_index = element->class->constant_pool[element->class->this_class - 1].info.Class.name_index;
    char name[100];
    get_utf8_value(class_index - 1, element->class->constant_pool, name);

    TEST_ASSERT_EQUAL(strcmp(name, "Carro"), 0);

    class_file_list_free(&cfl);
}
