#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "declarations.h"
#include "utils.h"
#include "xml_utils.h"
#include "table_utils.h"

long long TimeValue=0;
unsigned long long time_RDTSC()
{ union ticks
  { unsigned long long tx;
    struct dblword { long tl,th; } dw;
  } t;
  __asm("rdtsc\n": "=a"(t.dw.tl),"=d"(t.dw.th));
  return t.tx;
}

void time_start() { TimeValue=time_RDTSC(); }
long long time_stop() { return time_RDTSC()-TimeValue; }

int f1(SalesOrderDetail item1, SalesOrderDetail item2)
{
    if (item1.SalesOrderID < item2.SalesOrderID)
    {
        return -1;
    }
    if (item1.SalesOrderID > item2.SalesOrderID)
    {
        return 1;
    }
    return 0;
}

int f2(SalesOrderDetail item1, SalesOrderDetail item2)
{
    if (item1.ProductID < item2.ProductID)
    {
        return -1;
    }
    if (item1.ProductID > item2.ProductID)
    {
        return 1;
    }
    return 0;
}

int f3(SalesOrderDetail item1, SalesOrderDetail item2)
{
    if (item1.UnitPrice < item2.UnitPrice)
    {
        return -1;
    }
    if (item1.UnitPrice > item2.UnitPrice)
    {
        return 1;
    }
    return 0;
}

int searchf1(const void *item1, const void *item2)
{
    return ((*(SalesOrderDetail*)item1).SalesOrderID) - ((*(SalesOrderDetail*)item2).SalesOrderID);
}

int searchf2(const void *item1, const void *item2)
{
    return ((*(SalesOrderDetail*)item1).ProductID) - ((*(SalesOrderDetail*)item2).ProductID);
}

int searchf3(const void *item1, const void *item2)
{
    if (fabs(((*(SalesOrderDetail*)item1).UnitPrice) - ((*(SalesOrderDetail*)item2).UnitPrice)) < 1e-15)
    {
        return 0;
    }
    if (((*(SalesOrderDetail*)item1).UnitPrice) < ((*(SalesOrderDetail*)item2).UnitPrice))
    {
        return -1;
    }
    if (((*(SalesOrderDetail*)item1).UnitPrice) > ((*(SalesOrderDetail*)item2).UnitPrice))
    {
        return 1;
    }
    return 0;
}

int main(void)
{
    SalesOrderDetail *salesOrderDetail = NULL;
    int n = -1;

    char fileName[MAX_FILENAME_LENGTH];

    printf("%s", "Input file name: ");
    scanf("%s", fileName);

    FILE *f = fopen(fileName, "r");

    if (f == NULL)
    {
        puts("\nFile not found.");
        return -1;
    }

    int result = readTable(f, &salesOrderDetail, &n);

    switch (result)
    {
        case 0:
            printf("\nData from file %s succesfully loaded. \n\n", fileName);
            break;

        case 1:
            puts("Memory access error.");
            break;

        case -1:
            puts("\nError reading file.");
            break;

        case -2:
            puts("\nFile structure error.");
            break;
    }
    fclose(f);

    if (result != 0)
    {
        return 1;
    }

    printTable(salesOrderDetail, n);

    int menuItem = 0;
    SortFieldSelection:
    puts("\nSelect a field to search according to:");
    puts("[1] Sales Order ID");
    puts("[2] Product ID");
    puts("[3] Unit Price");
    printf("%c ", '>');
    if (scanf("%d", &menuItem) != 1)
    {
        puts("Item not found. Repeat input. \n");
        goto SortFieldSelection;
    }

    SalesOrderDetail key;
    SalesOrderDetail *item;

    unsigned long long int dt;
    switch (menuItem)
    {
        case 1:
            time_start();
            quickSort(salesOrderDetail, 0, n - 1, f1);
            dt = time_stop();

            puts("\nThe table was successfully sorted.\n");
            printf("Time (ns): %llu\n", dt);
            printTable(salesOrderDetail, n);

            SalesOrderIDInput:
            puts("\nInput Sales Order ID:");
            printf("%c ", '>');
            if (scanf("%d", &key.SalesOrderID) != 1)
            {
                puts("\nIllegal key. Repeat input.\n");
                goto SalesOrderIDInput;
            }
            item = (SalesOrderDetail*)bsearch((SalesOrderDetail*)(&key),
                                              (SalesOrderDetail*)salesOrderDetail,
                                              (unsigned int)n, sizeof(SalesOrderDetail), searchf1);
            if (item == NULL)
            {
                puts("\nItem not found.");
            }
            else
            {
                printItem(*item);
            }
            break;

        case 2:
            time_start();
            quickSort(salesOrderDetail, 0, n - 1, f2);

            dt = time_stop();

            puts("\nThe table was successfully sorted.\n");
            printf("Time (ns): %llu\n", dt);
            printTable(salesOrderDetail, n);

            ProductIDInput:
            puts("\nInput Product ID:");
            printf("%c ", '>');
            if (scanf("%d", &key.ProductID) != 1)
            {
                puts("\nIllegal key. Repeat input.\n");
                goto ProductIDInput;
            }
            item = (SalesOrderDetail*)bsearch((SalesOrderDetail*)(&key),
                                              (SalesOrderDetail*)salesOrderDetail,
                                              (unsigned int)n, sizeof(SalesOrderDetail), searchf2);
            if (item == NULL)
            {
                puts("\nItem not found.");
            }
            else
            {
                printItem(*item);
            }
            break;

        case 3:
            time_start();
            quickSort(salesOrderDetail, 0, n - 1, f3);

            dt = time_stop();

            puts("\nThe table was successfully sorted.\n");
            printf("Time (ns): %llu\n", dt);
            printTable(salesOrderDetail, n);

            UnitPriceInput:
            puts("\nInput Unit Price:");
            printf("%c ", '>');
            if (scanf("%f", &key.UnitPrice) != 1)
            {
                puts("\nIllegal key. Repeat input.\n");
                goto UnitPriceInput;
            }
            item = (SalesOrderDetail*)bsearch((SalesOrderDetail*)(&key),
                                              (SalesOrderDetail*)salesOrderDetail,
                                              (unsigned int)n, sizeof(SalesOrderDetail), searchf3);
            if (item == NULL)
            {
                puts("\nItem not found.");
            }
            else
            {
                printItem(*item);
            }
            break;

        default:
            puts("Item not found. Repeat input. \n");
            goto SortFieldSelection;
    }


    free(salesOrderDetail);
    return 0;
}
