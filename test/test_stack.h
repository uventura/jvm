#include "unity/unity.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/base/structures/stack.h"

void test_stack_is_empty_1(void)
{
    Stack my_stack;
    stack_initialize(&my_stack);
    TEST_ASSERT_EQUAL(1, stack_is_empty(&my_stack));
}

void test_stack_is_empty_2(void)
{
    Stack my_stack;
    stack_initialize(&my_stack);
    for (int i = 0; i < 10; i++)
    {
        stack_push(&my_stack, &i);
    }
    free_stack(&my_stack);
    TEST_ASSERT_EQUAL(1, stack_is_empty(&my_stack));
}

void test_stack_top_1(void)
{
    Stack my_stack;
    stack_initialize(&my_stack);
    int my_int = 42;
    stack_push(&my_stack, &my_int);
    int *my_int_2 = (int *)stack_top(&my_stack);
    TEST_ASSERT_EQUAL(42, *my_int_2);
    free_stack(&my_stack);
}

void test_stack_top_2(void)
{
    Stack my_stack;
    stack_initialize(&my_stack);
    int my_int = 42;
    for (int i = 0; i < 10; i++)
    {
        my_int++;
        stack_push(&my_stack, &my_int);
    }
    int *my_int_2 = (int *)stack_top(&my_stack);
    TEST_ASSERT_EQUAL(52, *my_int_2);
    free_stack(&my_stack);
}

void test_stack_push_pop_1(void)
{
    Stack my_stack;
    stack_initialize(&my_stack);
    int j = 0;
    for (int i = 0; i < 5; i++)
    {
        stack_push(&my_stack, &j);
        ++j;
    }
    int *top_of_stack;
    while (!stack_is_empty(&my_stack))
    {
        top_of_stack = (int *)stack_top(&my_stack);
        TEST_ASSERT_EQUAL(j--, *top_of_stack);
        stack_pop(&my_stack);
    }
}
