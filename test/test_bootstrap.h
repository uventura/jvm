#include "unity/unity.h"
#include <stdio.h>

#include "lib/class_loader/bootstrap/bootstrap.h"

void test_bootrstrap_get_cafe_babe(void)
{
    ClassFile class_file = load_class_file("data/examples/HelloWorld.class");
    TEST_ASSERT_EQUAL(class_file.magic, 0XCAFEBABE);
}
