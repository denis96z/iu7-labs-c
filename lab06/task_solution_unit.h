#ifndef TASK_SOLUTION_UNIT_H
#define TASK_SOLUTION_UNIT_H

int set_array_length(char **chain, int n);
void** set_matrix_length(int m, int m_size, int n, int n_size);
void free_matrix(void **matrix, int n);

int min_number(int a, int b);

void create_chain(char *chain1, int n);
int task_solution(char *chain1, int n1, char *chain2, int n2, char **subchain, int *n);

void print_chain(char *chain, int n);

#endif // TASK_SOLUTION_UNIT_H
