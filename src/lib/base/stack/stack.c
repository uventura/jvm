#include <stdio.h>
#include <stdlib.h>

#include "lib/base/stack/stack.h"

int is_empty(Stack *stack)
{
    if (stack->top == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

struct Node *create_node(void *data)
{
    Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void push(Stack *stack, void *data)
{
    Node *new_top = create_node(data);
    new_top->next = stack->top;
    stack->top = new_top;
}

struct Node *pop(Stack *stack)
{
    if (is_empty(stack))
    {
        fprintf(stderr, "ERROR: Attempted to pop from an empty stack\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        Node *temp = (stack->top);
        stack->top = (stack->top)->next;
        return temp;
    }
}

struct Node *top(Stack *stack)
{
    if (is_empty(stack))
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
    while (!is_empty(stack))
    {
        pop(stack);
    }
}
