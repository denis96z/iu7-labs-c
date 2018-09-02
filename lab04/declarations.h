#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define MAX_FILENAME_LENGTH 255

#define TABLE_LENGTH_INCREMENT 50

#define DATE_LENGTH 20

typedef struct
{
    int SalesOrderID;
    int SalesOrderDetailID;
    int OrderQty;
    int ProductID;
    float UnitPrice;
    float UnitPriceDiscount;
    char ModifiedDate[DATE_LENGTH];
} SalesOrderDetail;

typedef int(*tComparator)(SalesOrderDetail, SalesOrderDetail);

#endif // DECLARATIONS_H
