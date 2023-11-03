#include "unity/unity.h"
#include <stdio.h>

#include "test_read_bytes.h"
#include "test_bootstrap.h"

void setUp(void)
{
}

void tearDown(void)
{
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(testing_u2_read_cafe);
    RUN_TEST(testing_u2_read_babe);
    RUN_TEST(testing_u4_read_cafe_babe);
    RUN_TEST(test_bootrstrap_get_cafe_babe);
    return UNITY_END();
}
