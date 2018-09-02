#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "declarations.h"
#include "io_unit.h"

#define MAX_STRING_LENGTH 255

int read_data(sales_order_detail_t **sales_order_details, int *n)
{
    FILE *f = fopen("SalesOrderDetails.xml", "r");
    if (!f)
    {
        puts("FILE NOT FOUND!");
        return 0;
    }

    char str[MAX_STRING_LENGTH];

    if (!fgets(str, MAX_STRING_LENGTH, f))
    {
        puts("ERROR READING FILE!");
        return 0;
    }

    *n = 0;

    while (!feof(f))
    {
        if (!fgets(str, MAX_STRING_LENGTH, f))
        {
            puts("ERROR READING FILE!");
            return 0;
        }

        if (strncmp(str, "</ROOT>", 7) == 0)
        {
            return 1;
        }

        *n += 1;
        *sales_order_details = (sales_order_detail_t*)realloc(*sales_order_details,
                                                             (*n) * sizeof(sales_order_detail_t));
        if (!(*sales_order_details))
        {
            puts("MEMORY ALLOCATION ERROR!");
            return 0;
        }

        if (!read_xml_item(f, str))
        {
            puts("ERROR READING FILE!");
            return 0;
        }
        (*sales_order_details)[*n - 1].sales_order_ID = atoi(str);

        if (!read_xml_item(f, str))
        {
            puts("ERROR READING FILE!");
            return 0;
        }
        (*sales_order_details)[*n - 1].sales_order_detail_ID = atoi(str);

        if (!read_xml_item(f, str))
        {
            puts("ERROR READING FILE!");
            return 0;
        }
        (*sales_order_details)[*n - 1].order_qty = atoi(str);

        if (!read_xml_item(f, str))
        {
            puts("ERROR READING FILE!");
            return 0;
        }
        (*sales_order_details)[*n - 1].product_ID = atoi(str);

        if (!read_xml_item(f, str))
        {
            puts("ERROR READING FILE!");
            return 0;
        }
        (*sales_order_details)[*n - 1].unit_price = (float)atof(str);

        if (!read_xml_item(f, str))
        {
            puts("ERROR READING FILE!");
            return 0;
        }
        (*sales_order_details)[*n - 1].unit_price_discount = (float)atof(str);

        if (!read_xml_item(f, str))
        {
            puts("ERROR READING FILE!");
            return 0;
        }
        str_copy(str, (*sales_order_details)[*n - 1].modified_date, strlen(str));

        if (!fgets(str, MAX_STRING_LENGTH, f))
        {
            puts("ERROR READING FILE!");
            return 0;
        }

        //print_data((*sales_order_details)[*n - 1]);

    }

    return 1;
}


int read_xml_item(FILE *f, char *xml_item)
{
    assert(f);

    char str[MAX_STRING_LENGTH];

    if (!fgets(str, MAX_STRING_LENGTH, f))
    {
        puts("ERROR READING FILE!");
        return 0;
    }

    int left = str_pos(str, '>', 1) + 1;
    int right = str_pos(str, '<', 2) - 1;

    if ((left < 0) || (right < 0))
    {
        puts("ERROR READING FILE!");
        return 0;
    }

    int xml_item_pos = 0;
    for (int i = left; i <= right; i++)
    {
        xml_item[xml_item_pos++] = str[i];
    }
    xml_item[xml_item_pos] = '\0';

    return 1;
}


int str_pos(const char *str, char c, int n)
{
    int length = strlen(str);
    int items_found = 0;

    for (int i = 0; i < length; i++)
    {
        if (str[i] == c)
        {
            items_found++;
            if (items_found == n)
            {
                return i;
            }
        }
    }

    return -1;
}


int str_copy(const char *str1, char *str2, int n)
{
    for (int i = 0; i < n; i++)
    {
        str2[i] = str1[i];
    }
    str2[n] = '\0';
    return 1;
}


void print_data(sales_order_detail_t sales_order_detail)
{
    printf("Sales Order ID: %d\n", sales_order_detail.sales_order_ID);
    printf("Sales Order Detail ID: %d\n", sales_order_detail.sales_order_detail_ID);
    printf("Order Quantity: %d\n", sales_order_detail.order_qty);
    printf("Product ID: %d\n", sales_order_detail.product_ID);
    printf("Unit Price: %7.4f\n", sales_order_detail.unit_price);
    printf("Unit Price Discount: %7.4f\n", sales_order_detail.unit_price_discount);
    printf("Modified Date: %s\n", sales_order_detail.modified_date);
}
