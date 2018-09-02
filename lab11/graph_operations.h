#ifndef GRAPH_OPERATIONS_H
#define GRAPH_OPERATIONS_H

int allocate_graph_memory(graph_t *graph);
void free_graph_memory(graph_t *graph);

int read_adjacency_matrix(char *file_name, graph_t *graph);
void print_adjacency_matrix(const graph_t *graph);
int random_adjacency_matrix(graph_t *graph, int n);

void whiten_nodes(graph_t *graph);

int BDS(graph_t *graph);
int BDS_visit(graph_t *graph, int index, int *time);
int BFS(graph_t *graph, int start);

int top_sort(graph_t *graph, int *nodes);
int top_sort_visit(graph_t *graph, int index, int *nodes, int *nodes_index);

#endif // GRAPH_OPERATIONS_H
