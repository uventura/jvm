#include "unity/unity.h"
#include "lib/init/dummy.h"

void testing_unity_behavior(void)
{
  TEST_ASSERT_EQUAL(sum(1,0), 1);
}

