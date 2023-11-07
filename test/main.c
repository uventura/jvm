#include "unity/unity.h"
#include <stdio.h>

#include "test_bootstrap.h"
#include "test_read_bytes.h"

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
    RUN_TEST(test_bootstrap_get_cafe_babe);
    return UNITY_END();
}
