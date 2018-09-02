#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "declarations.h"
#include "table_utils.h"
#include "utils.h"

#define SALES_ORDER_ID_COLUMN_LENGTH 14
#define SALES_ORDER_DETAIL_ID_COLUMN_LENGTH 21
#define ORDER_QTY_COLUMN_LENGTH 9
#define PRODUCT_ID_COLUMN_LENGTH 10
#define UNIT_PRICE_COLUMN_LENGTH 10
#define UNIT_PRICE_DISCOUNT_COLUMN_LENGTH 19

void printItem(SalesOrderDetail item)
{
    printf("%-s", " Sales Order ID |");
    printf("%-s", " Sales Order Detail ID |");
    printf("%-s", " Order Qty |");
    printf("%-s", " Product ID |");
    printf("%-s", " Unit Price |");
    printf("%-s", " Unit Price Discount |");
    printf(" %*-s \n", DATE_LENGTH, "Modified Date");
    printf(" %*d |", SALES_ORDER_ID_COLUMN_LENGTH, item.SalesOrderID);
    printf(" %*d |", SALES_ORDER_DETAIL_ID_COLUMN_LENGTH, item.SalesOrderDetailID);
    printf(" %*d |", ORDER_QTY_COLUMN_LENGTH, item.OrderQty);
    printf(" %*d |", PRODUCT_ID_COLUMN_LENGTH, item.ProductID);
    printf(" %*.4f |", UNIT_PRICE_COLUMN_LENGTH, item.UnitPrice);
    printf(" %*.4f |", UNIT_PRICE_DISCOUNT_COLUMN_LENGTH, item.UnitPriceDiscount);
    printf(" %s \n", item.ModifiedDate);
}

void printTable(SalesOrderDetail *table, int n)
{
    assert(table != NULL);

    printf("%-s", " Sales Order ID |");
    printf("%-s", " Sales Order Detail ID |");
    printf("%-s", " Order Qty |");
    printf("%-s", " Product ID |");
    printf("%-s", " Unit Price |");
    printf("%-s", " Unit Price Discount |");
    printf(" %*-s \n", DATE_LENGTH, "Modified Date");

    for (int i = 0; i < n; i++)
    {
        printf(" %*d |", SALES_ORDER_ID_COLUMN_LENGTH, table[i].SalesOrderID);
        printf(" %*d |", SALES_ORDER_DETAIL_ID_COLUMN_LENGTH, table[i].SalesOrderDetailID);
        printf(" %*d |", ORDER_QTY_COLUMN_LENGTH, table[i].OrderQty);
        printf(" %*d |", PRODUCT_ID_COLUMN_LENGTH, table[i].ProductID);
        printf(" %*.4f |", UNIT_PRICE_COLUMN_LENGTH, table[i].UnitPrice);
        printf(" %*.4f |", UNIT_PRICE_DISCOUNT_COLUMN_LENGTH, table[i].UnitPriceDiscount);
        printf(" %s \n", table[i].ModifiedDate);
    }
}

void quickSort(SalesOrderDetail *table, int first, int last, tComparator f)
{
    int left;
    int right;
    SalesOrderDetail pivot;
    SalesOrderDetail temp;

    while (first < last)
    {
        pivot = table[(first + last) / 2];
        left = first - 1;
        right = last + 1;
        while (1)
        {
            do
            {
                right--;
            }
            while (f(table[right], pivot) > 0);
            do
            {
                left++;
            }
            while (f(table[left], pivot) < 0);
            if (left >= right)
            {
                break;
            }
            temp = table[left];
            table[left] = table[right];
            table[right] = temp;
        }
        if (first < right)
        {
            quickSort(table, first, right, f);
        }
        first = right + 1;
    }
}
