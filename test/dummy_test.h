#include "lib/init/dummy.h"
#include "unity/unity.h"

void
testing_unity_behavior (void)
{
  TEST_ASSERT_EQUAL (sum (1, 0), 1);
}
