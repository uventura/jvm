// Test library
#include "unity/unity.h"

// Other libraries
#include <malloc.h>
#include <string.h>

// Header from `src` directory
#include "lib/base/class_file/class_file.h"
#include "lib/base/class_file/cp_info.h"
#include "lib/class_loader/bootstrap/bootstrap.h"
#include "lib/class_loader/class_loader.h"

// Testing functionalities
void test_class_loader_recursive_single_class()
{
    ClassFile *class_file = (ClassFile *)malloc(sizeof(ClassFile));
    *class_file = load_class_file("data/examples/HelloWorld.class");

    char class_name[300];
    get_class_name(class_file->this_class, class_file->constant_pool, class_name);

    ClassFileList list = class_file_list_init();
    class_loader_recursive(class_file, &list, "data/examples/");
    TEST_ASSERT_EQUAL(1, list.num_elements);

    ClassFile *element = list.head->class;
    get_class_name(element->this_class, element->constant_pool, class_name);

    TEST_ASSERT_EQUAL(0, strcmp("HelloWorld", class_name));

    class_file_list_free(&list);
}

void test_class_loader_recursive_two_classes()
{
    ClassFile *class_file = (ClassFile *)malloc(sizeof(ClassFile));
    *class_file = load_class_file("data/examples/Carro.class");

    ClassFileList list = class_file_list_init();
    class_loader_recursive(class_file, &list, "data/examples/");

    TEST_ASSERT_EQUAL(2, list.num_elements);

    class_file_list_free(&list);
}
