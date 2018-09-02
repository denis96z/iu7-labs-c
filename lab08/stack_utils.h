#ifndef STACK_UTILS_H
#define STACK_UTILS_H

#include "declarations.h"

struct stack_node
{
    token_struct_t token;
    struct stack_node *next;
};

typedef struct stack_node stack_node_t;

int push(stack_node_t **stack_top, token_struct_t token);
token_struct_t pop(stack_node_t **stack_top);
token_struct_t stack_peek(stack_node_t *stack_top);
void clear_stack(stack_node_t **stack_top);
int stack_count(stack_node_t *stack_pointer);
int stack_is_empty(stack_node_t *stack_top);
void print_stack(stack_node_t *stack_top);

#endif // STACK_UTILS_H
