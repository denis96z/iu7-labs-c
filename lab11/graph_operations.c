#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "declarations.h"
#include "graph_operations.h"

int allocate_graph_memory(graph_t *graph)
{
    graph->nodes = (graph_node_t*)malloc(graph->n * sizeof(graph_node_t));
    if (!graph->nodes)
    {
        puts("MEMORY ALLOCATION ERROR!");
        return 0;
    }
    graph->adjacency_matrix = (int**)malloc(graph->n * sizeof(int*));
    if (!graph->adjacency_matrix)
    {
        puts("MEMORY ALLOCATION ERROR!");
        free(graph->nodes);
        return 0;
    }
    for (int i = 0; i < graph->n; i++)
    {
        graph->adjacency_matrix[i] = (int*)calloc(graph->n, sizeof(int));
        if (!graph->adjacency_matrix[i])
        {
            puts("MEMORY ALLOCATION ERROR!");
            free_graph_memory(graph);
            return 0;
        }
    }
    return 1;
}

void free_graph_memory(graph_t *graph)
{
    free(graph->nodes);
    for (int i = 0; i < graph->n; i++)
    {
        free(graph->adjacency_matrix[i]);
    }
    free(graph->adjacency_matrix);
}


int read_adjacency_matrix(char *file_name, graph_t *graph)
{
    FILE *f = fopen(file_name, "r");

    if (!f)
    {
        puts("FILE NOT FOUND!");
        return 0;
    }

    if (fscanf(f, "%d", &graph->n) != 1)
    {
        puts("ERROR READING FILE!");
        return 0;
    }

    if (!allocate_graph_memory(graph))
    {
        return 0;
    }

    for (int i = 0; i < graph->n; i++)
    {
        for (int j = 0; j < graph->n; j++)
        {
            if (fscanf(f, "%d", &graph->adjacency_matrix[i][j]) != 1)
            {
                puts("ERROR READING FILE!");
                return 0;
            }
        }
    }

    return 1;
}


int random_adjacency_matrix(graph_t *graph, int n)
{
    if (!n)
    {
        srand(time(0));
        graph->n = rand() % MATRIX_MAX_SIZE + MATRIX_MIN_SIZE;
    }
    else
    {
        graph->n = n;
    }

    if (!allocate_graph_memory(graph))
    {
        return 0;
    }

    for (int i = 0; i < graph->n; i++)
    {
        for (int j = 0; j < graph->n; j++)
        {
            if (i == j)
            {
                graph->adjacency_matrix[i][j] = 0;
            }
            else
            {
                graph->adjacency_matrix[i][j] = rand() % 2;
            }
        }
    }

    return 1;
}


void whiten_nodes(graph_t *graph)
{
    for (int i = 0; i < graph->n; i++)
    {
        graph->nodes[i].color = white_clr;
    }
}


int BDS(graph_t *graph)
{
    int time = 0;

    for (int i = 0; i < graph->n; i++)
    {
        if (graph->nodes[i].color == white_clr)
        {
            BDS_visit(graph, i, &time);
        }
    }

    return 1;
}

int BDS_visit(graph_t *graph, int index, int *time)
{
    printf("%d ", index);
    graph->nodes[index].color = gray_clr;
    graph->nodes[index].turns_gray_time = (*time)++;
    for (int i = 0; i < graph->n; i++)
    {
        if (!graph->adjacency_matrix[index][i])
        {
            continue;
        }
        if (graph->nodes[i].color == white_clr)
        {
            BDS_visit(graph, i, time);
        }
    }
    graph->nodes[index].color = black_clr;
    graph->nodes[index].turns_black_time = (*time)++;

    return 1;
}


void print_adjacency_matrix(const graph_t *graph)
{
    for (int i = 0; i < graph->n; i++)
    {
        for (int j = 0; j < graph->n; j++)
        {
            printf("%d ", graph->adjacency_matrix[i][j]);
        }
        printf("%c", '\n');
    }
    printf("%c", '\n');
}


int BFS(graph_t *graph, int start)
{
    int *queue = (int*)calloc(graph->n, sizeof(int));
    if (!queue)
    {
        puts("MEMORY ALLOCATION ERROR!");
        return 0;
    }

    int count = 0;
    int head = 0;

    for (int i = 0; i < graph->n; i++)
    {
        queue[i] = 0;
    }

    queue[count++] = start;
    graph->nodes[start].color = black_clr;

    while (head < count)
    {
        start = queue[head++];
        printf("%d ", start);
        for (int i = 0; i < graph->n; i++)
        {
            if (graph->adjacency_matrix[start][i] && (graph->nodes[i].color == white_clr))
            {
                queue[count++] = i;
                graph->nodes[i].color = black_clr;
            }
        }
    }

    free(queue);

    return 1;
}


int top_sort(graph_t *graph, int *nodes)
{
    int nodes_index = 0;
    for (int i = 0; i < graph->n; i++)
    {
        if (!top_sort_visit(graph, i, nodes, &nodes_index))
        {
            return 0;
        }
    }
    return 1;
}


int top_sort_visit(graph_t *graph, int index, int *nodes, int *nodes_index)
{
    if (graph->nodes[index].color == black_clr)
    {
        return 1;
    }
    if (graph->nodes[index].color == gray_clr)
    {
        return 0;
    }
    graph->nodes[index].color = gray_clr;
    for (int i = 0; i < graph->n; i++)
    {
        if (graph->adjacency_matrix[index][i])
        {
            if (!top_sort_visit(graph, i, nodes, nodes_index))
            {
                return 0;
            }
        }
    }
    graph->nodes[index].color = black_clr;
    nodes[*nodes_index] = index;
    *nodes_index += 1;
    return 1;
}
