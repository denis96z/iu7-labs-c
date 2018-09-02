#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue_utils.h"

int enqueue(queue_node_t **queue_head, queue_node_t **queue_tail, token_struct_t token)
{
    queue_node_t *new_queue_node = (queue_node_t*)malloc(sizeof(queue_node_t));
    if (!new_queue_node)
    {
        return 0;
    }
    new_queue_node->token = token;
    new_queue_node->next = NULL;
    if (queue_is_empty(*queue_head))
    {
        *queue_head = new_queue_node;
    }
    else
    {
        (*queue_tail)->next = new_queue_node;
    }
    *queue_tail = new_queue_node;
    return 1;
}

token_struct_t dequeue(queue_node_t **queue_head, queue_node_t **queue_tail)
{
    assert(*queue_head);

    token_struct_t token = (*queue_head)->token;
    queue_node_t *temp = *queue_head;
    *queue_head = (*queue_head)->next;
    if (!(*queue_head))
    {
        *queue_tail = NULL;
    }
    free(temp);
    return token;
}

token_struct_t queue_peek(queue_node_t *queue_head)
{
    token_struct_t token = queue_head->token;
    return token;
}

void clear_queue(queue_node_t **queue_head, queue_node_t **queue_tail)
{
    token_struct_t token;
    while (!queue_is_empty(*queue_head))
    {
        token = dequeue(queue_head, queue_tail);
        free(token.name);
    }
    return;
}

int queue_count(queue_node_t *queue_head)
{
    if (!queue_head)
    {
        return 0;
    }
    return queue_count(queue_head->next) + 1;
}

int queue_is_empty(queue_node_t *queue_head)
{
    return queue_head == NULL;
}

void print_queue(queue_node_t *queue_head)
{
    queue_node_t *temp = queue_head;
    while (temp)
    {
        printf("%s ", temp->token.name);
        temp = temp->next;
    }
    puts("");
}
