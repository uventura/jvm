#include "unity/unity.h"

#include "dummy_test.h"

void setUp(void)
{
  /* This is run before EACH TEST */
}

void tearDown(void){
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(testing_unity_behavior);
    return UNITY_END();
}
