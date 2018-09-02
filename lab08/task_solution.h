#ifndef TASK_SOLUTION_H
#define TASK_SOLUTION_H

#include "queue_utils.h"

int set_tokens_array_length(token_struct_t **, int);
int add_token(char *str, token_t type, token_struct_t **, int *);

int infix_to_reversed(char *expression, queue_node_t **queue_head, queue_node_t **queue_tail);

int count_result(queue_node_t *queue_head, double *result);

#endif // TASK_SOLUTION_H
