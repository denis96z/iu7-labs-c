#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "task_solution_unit.h"

int main(void)
{
    int n1 = 0, n2 = 0; // Длина каждой цепочки.
    char *chain1 = NULL; // Первая цепочка.
    char *chain2 = NULL; // Вторая цепочка.

    int n = 0;
    char *subchain = NULL;

    // Считываем длину каждой цепочки.
    puts("Input first chain length: ");
    printf("%c ", '>');
    scanf("%d", &n1);
    puts("Input second chain length: ");
    printf("%c ", '>');
    scanf("%d", &n2);

    // Выделяем память под цепочки.
    if (!set_array_length(&chain1, n1))
    {
        puts("MEMORY ACCESS VIOLATION");
        return 1;
    }
    if (!set_array_length(&chain2, n2))
    {
        puts("MEMORY ACCESS VIOLATION");
        return 1;
    }
    if (!set_array_length(&subchain, min_number(n1, n2)))
    {
        puts("MEMORY ACCESS VIOLATION");
        return 1;
    }

    create_chain(chain1, n1);
    create_chain(chain2, n2);

    task_solution(chain1, n1, chain2, n2, &subchain, &n);

    puts("\nChain 1: \n");
    print_chain(chain1, n1);
    puts("\nChain 2: \n");
    print_chain(chain2, n2);
    if (n > 0)
    {
        puts("\nLongest subchain: \n");
        print_chain(subchain, n);
    }
    else
    {
        puts("\nSubchains not found.");
    }

    free(chain1);
    free(chain2);
    free(subchain);

    getch();
    return 0;
}
