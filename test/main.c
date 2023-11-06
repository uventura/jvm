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
    //TESTING GENERAL INFORMATIONS OF .CLASS SOMA (interface)
    RUN_TEST(test_bootstrap_get_cafe_babe_soma);
    RUN_TEST(test_bootstrap_constant_pool_count_soma);
    RUN_TEST(test_bootstrap_access_flags_soma);
    RUN_TEST(test_bootstrap_interfaces_count_soma);
    RUN_TEST(test_bootstrap_fields_count_soma);
    RUN_TEST(test_bootstrap_methods_count_soma);
    RUN_TEST(test_bootstrap_attributes_count_soma);
    return UNITY_END();
}
