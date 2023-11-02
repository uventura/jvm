#include "unity/unity.h"
#include <stdio.h>

#include "lib/base/file/read_bytes.h"

void testing_u2_read_cafe(void)
{
    FILE* hello_world = fopen("test/data/examples/HelloWorld.class", "rb");

    u2 cafe = u2_read(hello_world);

    TEST_ASSERT_EQUAL(cafe, 0XCAFE);
    fclose(hello_world);
}

void testing_u2_read_babe(void)
{
    FILE* hello_world = fopen("test/data/examples/HelloWorld.class", "rb");

    u2_read(hello_world);
    u2 babe = u2_read(hello_world);

    TEST_ASSERT_EQUAL(babe, 0XBABE);
    fclose(hello_world);
}

void testing_u4_read_cafe_babe(void)
{
   FILE* hello_world = fopen("test/data/examples/HelloWorld.class", "rb");

   u4 cafe_babe = u4_read(hello_world);
   TEST_ASSERT_EQUAL(cafe_babe, 0XCAFEBABE);

   fclose(hello_world);
}
