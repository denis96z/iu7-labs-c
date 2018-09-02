#include <stdlib.h>
#include <stdio.h>

#include "task_solution_unit.h"

#define SYMBOLS_NUM 26

void find_longest_subchain(char **subchain, int *n, char **b, char *chain1, int i, int j);

int random_number(int min, int max)
{
    int n;
    n = (rand() % (max - min)) + min;
    return n;
}

int set_array_length(char **chain, int n)
{
    *chain = (char*)malloc(n * sizeof(char));
    if (!(*chain))
    {
        return 0;
    }
    return 1;
}

void** set_matrix_length(int m, int m_size, int n, int n_size)
{
    void **matrix = malloc(m * m_size);
    if (!matrix)
    {
        return NULL;
    }
    for (int i = 0; i < m; i++)
    {
        matrix[i] = malloc(n * n_size);
        if (!matrix[i])
        {
            free_matrix(matrix, i);
            return NULL;
        }
    }
    return matrix;
}

void free_matrix(void **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void create_chain(char *chain1, int n)
{
    const char symbols[SYMBOLS_NUM] =
    {
        'A', 'B', 'C', 'D', 'E', 'F',
        'G', 'H', 'I', 'J', 'K', 'L',
        'M', 'N', 'O', 'P', 'Q', 'R',
        'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z'
    };
    for (int i = 0; i < n; i++)
    {
        chain1[i] = symbols[random_number(0, SYMBOLS_NUM)];
    }
}

int min_number(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}

int task_solution(char *chain1, int n1, char *chain2, int n2, char **subchain, int *n)
{
    int **c = (int**)set_matrix_length(n1 + 1, sizeof(int*), n2 + 1, sizeof(int));
    if (!c)
    {
        puts("MEMORY ACCESS ERROR");
        return -1;
    }

    char **b = (char**)set_matrix_length(n1, sizeof(char*), n2, sizeof(char));
    if (!b)
    {
        puts("MEMORY ACCESS ERROR");
        return -1;
    }

    int i = 0, j = 0;
    for (i = 0; i <= n1; i++)
    {
        c[i][0] = 0;
    }
    for (j = 0; j <= n1; j++)
    {
        c[0][j] = 0;
    }
    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < n2; j++)
        {
            if (chain1[i] == chain2[j])
            {
                c[i + 1][j + 1] = c[i][j] + 1;
                b[i][j] = '\\';
            }
            else if (c[i][j + 1] >= c[i + 1][j])
            {
                c[i + 1][j + 1] = c[i][j + 1];
                b[i][j] = '|';
            }
            else
            {
                c[i + 1][j + 1] = c[i + 1][j];
                b[i][j] = '-';
            }
        }
    }

    find_longest_subchain(subchain, n, b, chain1, n1 - 1, n2 - 1);

    free_matrix((void**)c, n2 + 1);
    free_matrix((void**)b, n2);
    return 0;
}

void find_longest_subchain(char **subchain, int *n, char **b, char *chain1, int i, int j)
{
    if ((i < 0) || (j < 0))
    {
        return;
    }
    if (b[i][j] == '\\')
    {
        find_longest_subchain(subchain, n, b, chain1, i - 1, j - 1);
        (*subchain)[*n] = chain1[i];
        (*n)++;
    }
    else if (b[i][j] == '|')
    {
        find_longest_subchain(subchain, n, b, chain1, i - 1, j);
    }
    else
    {
        find_longest_subchain(subchain, n, b, chain1, i, j - 1);
    }
}

void print_chain(char *chain, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c", chain[i]);
    }
    puts("");
}
