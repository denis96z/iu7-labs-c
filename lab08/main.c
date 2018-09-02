#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declarations.h"
#include "task_solution.h"
#include "queue_utils.h"

int contains(variable_t *variables, int n, char *str)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(variables[i].name, str) == 0)
        {
            return 1;
        }
    }
    return 0;
}


#define MAX_STRING_LENGTH 255
int main(void)
{
    char expression[MAX_STRING_LENGTH] = "";
    puts("Input expression:");
    if (!fgets(expression, MAX_STRING_LENGTH, stdin))
    {
        puts("Error reading expression");
        return 1;
    }
    expression[strlen(expression) - 1] = '\0';

    queue_node_t *queue_head = NULL;
    queue_node_t *queue_tail = NULL;

    if (!infix_to_reversed(expression, &queue_head, &queue_tail))
    {
        puts("ERROR");
        return 1;
    }
    puts("\nPostfix Polish notation:");
    print_queue(queue_head);

    queue_node_t *queue_pointer = queue_head;
    int n_var = 0;
    while (queue_pointer)
    {
        if (queue_pointer->token.type == variable)
        {
            n_var++;
        }
        queue_pointer = queue_pointer->next;
    }
    if (n_var > 0)
    {
        puts("\nInput the values of variables:");
        queue_pointer = queue_head;
        while (queue_pointer)
        {
            if (queue_pointer->token.type == variable)
            {
                float value = 0.0;
                ValueInput:
                printf("%s = ", queue_pointer->token.name);
                if (scanf("%f", &value) != 1)
                {
                    puts("INCORRECT INPUT");
                    goto ValueInput;
                }
                queue_pointer->token.value = (double)value;
            }
            else if (queue_pointer->token.type == constant)
            {
                queue_pointer->token.value = atof(queue_pointer->token.name);
            }
            queue_pointer = queue_pointer->next;
        }
    }

    double result = 0.0;
    if (!count_result(queue_head, &result))
    {
        return -1;
    }
    printf("\nResult = %7.4f\n", (float)result);

    return 0;
}
