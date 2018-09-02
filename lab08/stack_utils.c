#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack_utils.h"

int push(stack_node_t **stack_top, token_struct_t token)
{
    stack_node_t *temp = (stack_node_t*)malloc(sizeof(stack_node_t));
    if (!temp)
    {
        return 0;
    }
    temp->token = token;
    temp->next = *stack_top;
    *stack_top = temp;
    return 1;
}

token_struct_t pop(stack_node_t **stack_top)
{
    assert(*stack_top);

    stack_node_t *temp = *stack_top;
    token_struct_t token = (*stack_top)->token;
    *stack_top = (*stack_top)->next;
    free(temp);
    return token;
}

token_struct_t stack_peek(stack_node_t *stack_top)
{
    assert(stack_top);

    token_struct_t token = stack_top->token;
    return token;
}

void clear_stack(stack_node_t **stack_top)
{
    token_struct_t token;
    while (!stack_is_empty(*stack_top))
    {
        token = pop(stack_top);
        free(token.name);
    }
    return;
}

int stack_count(stack_node_t *stack_pointer)
{
    if (!stack_pointer)
    {
        return 0;
    }
    return stack_count(stack_pointer->next) + 1;
}

int stack_is_empty(stack_node_t *stack_top)
{
    return stack_top == NULL;
}

void print_stack(stack_node_t *stack_top)
{
    stack_node_t *temp = stack_top;
    while (temp)
    {
        printf("%s ", temp->token.name);
        temp = temp->next;
    }
    puts("");
}
