#ifndef TASK_SOLUTION_H
#define TASK_SOLUTION_H

typedef int(*task_solution_t)(FILE *f_products, FILE *f_suppliers, FILE *f_shipments);

int task1_solution(FILE *f_products, FILE *f_suppliers, FILE *f_shipments);
int task2_solution(FILE *f_products, FILE *f_suppliers, FILE *f_shipments);
int task3_solution(FILE *f_products, FILE *f_suppliers, FILE *f_shipments);
int task4_solution(FILE *f_products, FILE *f_suppliers, FILE *f_shipments);
int task5_solution(FILE *f_products, FILE *f_suppliers, FILE *f_shipments);

#endif // TASK_SOLUTION_H
