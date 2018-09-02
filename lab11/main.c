#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declarations.h"
#include "graph_operations.h"


void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

int main(int argc, char *argv[])
{
    graph_t graph;
    graph.n = 0;
    graph.nodes = NULL;
    graph.adjacency_matrix = NULL;

    if (argc > 1)
    {
        if (strcmp(argv[1], "-r") == 0)
        {
            if (!random_adjacency_matrix(&graph, 0))
            {
                goto ProgramExitPoint;
            }
        }
        else if (strcmp(argv[1], "-s") == 0)
        {
            if (argc != 3)
            {
                puts("INVALID ARGUMENTS FORMAT!");
                goto ProgramExitPoint;
            }
            int size = atoi(argv[2]);
            if (!random_adjacency_matrix(&graph, size))
            {
                goto ProgramExitPoint;
            }
        }
        else if (strcmp(argv[1], "-f") == 0)
        {
            if (argc != 3)
            {
                puts("INVALID ARGUMENTS FORMAT!");
                goto ProgramExitPoint;
            }
            if (!read_adjacency_matrix(argv[2], &graph))
            {
                goto ProgramExitPoint;
            }
        }
    }
    else
    {
        //if (!input_adjacency_matrix(&graph))
        {
            goto ProgramExitPoint;
        }
    }

    if (graph.n <= MAX_SIZE_TO_PRINT)
    {
        puts("Adjacency matrix:");
        print_adjacency_matrix(&graph);
    }

    puts("Depth search:");
    whiten_nodes(&graph);
    BDS(&graph);
    printf("%c", '\n');

    puts("Width search:");
    whiten_nodes(&graph);
    BFS(&graph, 0);
    printf("%c", '\n');

    int *nodes = (int*)calloc(graph.n, sizeof(int));
    if (!nodes)
    {
        puts("MEMORY ALLOCATION ERROR!");
        goto ProgramExitPoint;
    }

    puts("Topological sort:");
    whiten_nodes(&graph);
    if (top_sort(&graph, nodes))
    {
        for (int i = 0; i < graph.n / 2; i++)
        {
            swap(&nodes[i], &nodes[graph.n - i - 1]);
        }
        for (int i = 0; i < graph.n; i++)
        {
            printf("%d ", nodes[i]);
        }
        printf("%c", '\n');
    }
    else
    {
        puts("CYCLE FOUND!");
    }

    ProgramExitPoint:
    free_graph_memory(&graph);

    return 0;
}
