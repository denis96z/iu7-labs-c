#ifndef QUEUE_UTILS_H
#define QUEUE_UTILS_H

#include "declarations.h"

struct queue_node
{
    token_struct_t token;
    struct queue_node *next;
};

typedef struct queue_node queue_node_t;

int enqueue(queue_node_t **queue_head, queue_node_t **queue_tail, token_struct_t token);
token_struct_t dequeue(queue_node_t **queue_head, queue_node_t **queue_tail);
token_struct_t queue_peek(queue_node_t *queue_head);
void clear_queue(queue_node_t **queue_head, queue_node_t **queue_tail);
int queue_count(queue_node_t *queue_head);
int queue_is_empty(queue_node_t *queue_head);
void print_queue(queue_node_t *queue_head);

#endif // QUEUE_UTILS_H
