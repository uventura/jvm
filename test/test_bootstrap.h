#include "unity/unity.h"

#include <stdio.h>
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
