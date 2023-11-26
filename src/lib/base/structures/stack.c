#include <stdio.h>
#include <stdlib.h>

#include "lib/base/defines.h"
#include "lib/base/structures/stack.h"

void stack_initialize(Stack* stack) {
    stack->top = NULL;
}

int stack_is_empty(Stack *stack)
{
    if (stack->top == NULL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

struct Node *stack_create_node(void *data)
{
    Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void stack_push(Stack *stack, void *data)
{
    Node *new_top = stack_create_node(data);
    new_top->next = stack->top;
    stack->top = new_top;
}

void stack_pop(Stack *stack)
{
    if (stack_is_empty(stack))
    {
        fprintf(stderr, "ERROR: Attempted to pop from an empty stack\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        Node *temp = (stack->top);
        stack->top = (stack->top)->next;
        free(temp);
    }
}

struct Node *stack_top(Stack *stack)
{
    if (stack_is_empty(stack))
    {
        fprintf(stderr, "ERROR: Attempted to access top element of an empty stack\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        return (stack->top)->data;
    }
}

void free_stack(Stack *stack)
{
    struct Node *current_node;
    while (!stack_is_empty(stack))
    {
        current_node = (stack->top)->next;
        free(stack->top);
        stack->top = current_node;
    }
}
