#ifndef TABLE_UTILS_H
#define TABLE_UTILS_H

void printItem(SalesOrderDetail item);

void printTable(SalesOrderDetail *table, int n);

void quickSort(SalesOrderDetail *table, int first, int last, tComparator f);

#endif // TABLE_UTILS_H
