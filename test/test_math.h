// Test library
#include "unity/unity.h"

// Header from `src` directory
#include "lib/base/math/iee754.h"

// Testing functionalities
void test_iee754_single_get(void)
{
    float result = ieee754_single(0x4019999a);
    float expected = 2.4;
    TEST_ASSERT_EQUAL(result, expected);
}

void test_iee754_double_get(void)
{
    double result = ieee754_single(0x4019999a);
    double expected = 2.4;
    TEST_ASSERT_EQUAL(result, expected);
}
