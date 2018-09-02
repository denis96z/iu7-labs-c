#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define MAX_SIZE_TO_PRINT 10

#define MATRIX_MIN_SIZE 100
#define MATRIX_MAX_SIZE 1000

typedef enum
{
    white_clr,
    gray_clr,
    black_clr
} color_t;

typedef struct
{
    color_t color;
    int turns_gray_time;
    int turns_black_time;
} graph_node_t;

typedef struct
{
    graph_node_t *nodes;
    int **adjacency_matrix;
    int n;
} graph_t;

#endif // DECLARATIONS_H
