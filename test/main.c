#include "unity/unity.h"
#include <stdio.h>

#include "test_bootstrap.h"
#include "test_class_file_list.h"
#include "test_class_loader.h"
#include "test_method_area.h"
#include "test_read_bytes.h"
#include "test_stack.h"

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
    // TESTING GENERAL INFORMATIONS OF .CLASS SOMA (interface)
    RUN_TEST(test_bootstrap_get_cafe_babe_soma);
    RUN_TEST(test_bootstrap_constant_pool_count_soma);
    RUN_TEST(test_bootstrap_access_flags_soma);
    RUN_TEST(test_bootstrap_interfaces_count_soma);
    RUN_TEST(test_bootstrap_fields_count_soma);
    RUN_TEST(test_bootstrap_methods_count_soma);
    RUN_TEST(test_bootstrap_attributes_count_soma);

    // TESTING GENERAL INFORMATIONS OF .CLASS MATEMATICO

    RUN_TEST(test_bootstrap_get_cafe_babe_matematico);
    RUN_TEST(test_bootstrap_constant_pool_count_matematico);
    RUN_TEST(test_bootstrap_access_flags_matematico);
    RUN_TEST(test_bootstrap_interfaces_count_matematico);
    RUN_TEST(test_bootstrap_fields_count_matematico);
    RUN_TEST(test_bootstrap_methods_count_matematico);
    RUN_TEST(test_bootstrap_attributes_count_matematico);

    // TESTING GENERAL INFORMATIONS OF .CLASS CARRO

    RUN_TEST(test_bootstrap_get_cafe_babe_carro);
    RUN_TEST(test_bootstrap_constant_pool_count_carro);
    RUN_TEST(test_bootstrap_access_flags_carro);
    RUN_TEST(test_bootstrap_interfaces_count_carro);
    RUN_TEST(test_bootstrap_fields_count_carro);
    RUN_TEST(test_bootstrap_methods_count_carro);
    RUN_TEST(test_bootstrap_attributes_count_carro);

    // TESTING STACK STRUCTURE

    RUN_TEST(test_stack_is_empty_1);
    RUN_TEST(test_stack_is_empty_2);
    RUN_TEST(test_stack_top_1);
    RUN_TEST(test_stack_top_2);
    RUN_TEST(test_stack_push_pop_1);

    // TESTING CLASS FILE LIST
    RUN_TEST(test_class_file_list_initialization);
    RUN_TEST(test_class_file_list_loading_single_class);
    RUN_TEST(test_class_file_list_double_insert);
    RUN_TEST(test_class_file_list_two_classes);

    // TESTING CLASS LOADER FUNCTIONALITY
    RUN_TEST(test_class_loader_recursive_single_class);
    RUN_TEST(test_class_loader_recursive_two_classes);

    // TEST METHOD AREA
    RUN_TEST(test_get_method_by_name_existent);
    RUN_TEST(test_get_method_non_existent);

    return UNITY_END();
}
