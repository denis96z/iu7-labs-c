#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "declarations.h"
#include "utils.h"
#include "xml_utils.h"

#define MAX_STRING_LENGTH 255

#define MAX_FIELD_LENGTH 30

#define LENGTH_INCREMENT 50

int readTable(FILE *f, SalesOrderDetail **table, int *n)
{
    char str[MAX_STRING_LENGTH]; // Считываемая из файла строка.
    int tableLength = 0;         // Количество строк в таблице.

    // Файл должен быть предварительно открыт.
    assert(f != NULL);

    // Читаем из файла все строки.
    while (fgets(str, MAX_STRING_LENGTH, f) != NULL)
    {
        if (strncmp(str, "<SalesOrderDetail>", 18) == 0)
        {
            // Увеличиваем, длину массива.
            (*n)++;

            if (*n == tableLength)
            {
                tableLength += LENGTH_INCREMENT;
                if (setLength(table, tableLength) == false)
                {
                    return 1;
                }
            }

            // Считываем в таблицу данные из файла.
            // SalesOrderID
            if (fgets(str, MAX_STRING_LENGTH, f) != NULL)
            {
                if (parseString(str) == false)
                {
                    return -2;
                }
                (*table)[*n].SalesOrderID = atoi(str);
            }
            else
            {
                return -1;
            }

            // SalesOrderDetailID
            if (fgets(str, MAX_STRING_LENGTH, f) != NULL)
            {
                if (parseString(str) == false)
                {
                    return -2;
                }
                (*table)[*n].SalesOrderDetailID = atoi(str);
            }
            else
            {
                return -1;
            }

            // OrderQty
            if (fgets(str, MAX_STRING_LENGTH, f) != NULL)
            {
                if (parseString(str) == false)
                {
                    return -2;
                }
                (*table)[*n].OrderQty = atoi(str);
            }
            else
            {
                return -1;
            }

            // ProductID
            if (fgets(str, MAX_STRING_LENGTH, f) != NULL)
            {
                if (parseString(str) == false)
                {
                    return -2;
                }
                (*table)[*n].ProductID = atoi(str);
            }
            else
            {
                return -1;
            }

            // UnitPrice
            if (fgets(str, MAX_STRING_LENGTH, f) != NULL)
            {
                if (parseString(str) == false)
                {
                    return -2;
                }
                (*table)[*n].UnitPrice = (float)atof(str);
            }
            else
            {
                return -1;
            }

            // UnitPriceDiscount
            if (fgets(str, MAX_STRING_LENGTH, f) != NULL)
            {
                if (parseString(str) == false)
                {
                    return -2;
                }
                (*table)[*n].UnitPriceDiscount = (float)atof(str);
            }
            else
            {
                return -1;
            }

            // ModifiedDate
            if (fgets(str, MAX_STRING_LENGTH, f) != NULL)
            {
                if (parseString(str) == false)
                {
                    return -2;
                }
                strncpy((*table)[*n].ModifiedDate, str, DATE_LENGTH);
            }
            else
            {
                return -1;
            }
        }
    }

    // Теперь n - не индекс последнего элемента, а количество элементов.
    (*n)++;

    if (setLength(table, *n) == false)
    {
        return 2;
    }

    return 0;
}

bool parseString(char *str)
{
    char strcopy[MAX_STRING_LENGTH];

    int length = 0;
    int i1 = -1;
    int i2 = -1;

    int counter = -1;

    length = strlen(str);
    for (int i = 0; i < length; i++)
    {
        if ((str[i] == '>') && (i1 == -1))
        {
            i1 = i + 1;
        }
        if ((str[i] == '/') && (i2 == -1))
        {
            i2 = i - 2;
        }
    }

    if ((i1 == -1) || (i2 == -1))
    {
        return false;
    }

    strcpy(strcopy, "");
    for (int i = i1; i <= i2; i++)
    {
        counter++;
        strcopy[counter] = str[i];
    }
    strcopy[counter + 1] = '\0';
    strcpy(str, strcopy);

    return true;
}
