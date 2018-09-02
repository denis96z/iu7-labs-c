#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define MAX_DATE_SYMBOLS 20

typedef struct
{
    int sales_order_ID;
    int sales_order_detail_ID;
    int order_qty;
    int product_ID;
    float unit_price;
    float unit_price_discount;
    char modified_date[MAX_DATE_SYMBOLS];
} sales_order_detail_t;


typedef struct tree_node_t
{
    sales_order_detail_t *sales_order_detail;
    struct tree_node_t *left, *right;
} tree_node_t;


typedef int(*cmp_f_t)(const sales_order_detail_t *item1, const sales_order_detail_t *item2);


#endif // DECLARATIONS_H
