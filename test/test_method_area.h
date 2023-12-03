#include "unity/unity.h"

// Header from `src` directory
#include "lib/base/class_file/method_info.h"
#include "lib/class_loader/bootstrap/bootstrap.h"
#include "lib/runtime_data_area/method_area.h"

#include <string.h>

// Testing functionalities
void test_get_method_by_name_existent(void)
{
    ClassFile class_file = load_class_file("data/examples/Matematico.class");
    method_info *method = method_area_search_method("getSoma", &class_file);

    char method_name[200];
    get_utf8_value(method->name_index - 1, class_file.constant_pool, method_name);

    TEST_ASSERT_NOT_EQUAL(method, NULL);
    TEST_ASSERT_EQUAL(strcmp("getSoma", method_name), 0);

    free_class_file(class_file);
}

void test_get_method_non_existent(void)
{
    ClassFile class_file = load_class_file("data/examples/Matematico.class");
    method_info *method = method_area_search_method("getSomaaaa", &class_file);

    TEST_ASSERT_EQUAL(method, NULL);

    free_class_file(class_file);
}
