#ifndef JVM_STACK_STRUCT
#define JVM_STACK_STRUCT

typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

typedef struct
{
    Node *top;
} Stack;

int stack_is_empty(Stack *stack);
struct Node *stack_create_node(void *data);
void stack_push(Stack *stack, void *data);
struct Node *stack_pop(Stack *stack);
struct Node *stack_top(Stack *stack);
void free_stack(Stack *stack);

#endif
