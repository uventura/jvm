# How to Create Tests?

1. Create a test file in this directory, e.g. `my_test.h`
2. Define your tests:
```C
// Test library
#include "unity/unity.h"

// Header from `src` directory
#include "lib/dummy.h"

// Testing functionalities
void test_hakuna_matata(void)
{
  TEST_ASSERT_EQUAL(1, 1);
}

void test_potato_potato(void)
{
  TEST_ASSERT_EQUAL("potato", "potato");
}

[...]
```
3. Include in `main.c`:
```C
#include "unity/unity.h"

#include "my_test.h"

void setUp(void){}

void tearDown(void){}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_hakuna_matata);
    RUN_TEST(test_potato_potato);
    return UNITY_END();
}
```
4.Run test with `make test`

More about doing tests you can find here http://www.throwtheswitch.org/unity
