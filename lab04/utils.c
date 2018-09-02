#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "declarations.h"

#include "utils.h"

bool setLength(SalesOrderDetail **table, int n)
{
    if (*table == NULL)
    {
        *table = (SalesOrderDetail*)malloc(n * sizeof(SalesOrderDetail));
    }
    else
    {
        *table = (SalesOrderDetail*)realloc(*table, n * sizeof(SalesOrderDetail));
    }

    if (*table == NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void trimRight(char *str)
{
    unsigned int length = strlen(str);
    for (unsigned int i = (length - 1); i >= 0; i--)
    {
        if (str[i] == ' ')
        {
            str[i] = '\0';
        }
    }
}
