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

int is_empty(Stack *stack);
struct Node *create_node(void *data);
void push(Stack *stack, void *data);
struct Node *pop(Stack *stack);
struct Node *top(Stack *stack);
void free_stack(Stack *stack)

#endif
