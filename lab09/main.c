#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"
#include "io_unit.h"
#include "tree_operations.h"

#define MAX_FILE_NAME_LENGTH 255

int main(void)
{
    sales_order_detail_t *sales_order_details = NULL;
    int n = 0;

    if (!read_data(&sales_order_details, &n))
    {
        goto ProgramExitPoint;
    }

    tree_node_t *root = NULL;
    cmp_f_t cmp_f = compare_sales_order_ID;

    int key = 1;
    int menu_item = 0;

    puts("Select key:");
    puts("[1] Sales Order ID");
    puts("[2] Sales Order Detail ID");
    puts("[3] Order Quantity");
    puts("[4] Product ID");
    puts("[5] Unit Price");
    puts("[6] Unit Price Discount");
    scanf("%d", &key);
    switch (key)
    {
        case 1:
            cmp_f = compare_sales_order_ID;
            break;

        case 2:
            cmp_f = compare_sales_order_detail_ID;
            break;

        case 3:
            cmp_f = compare_order_qty;
            break;

        case 4:
            cmp_f = compare_product_ID;
            break;

        case 5:
            cmp_f = compare_unit_price;
            break;

        case 6:
            cmp_f = compare_unit_price_discount;
            break;
    }


    for (int i = 0; i < n; i++)
    {
        tree_node_t *node = create_node(&sales_order_details[i]);
        if (!node)
        {
            goto ProgramExitPoint;
        }
        if (!insert_node(node, &root, cmp_f))
        {
            goto ProgramExitPoint;
        }
    }

    puts("Prefix search:");
    prefix_search(root);
    printf("%s", "\n\n");
    puts("Infix search:");
    infix_search(root);
    printf("%s", "\n\n");
    puts("Postfix search:");
    postfix_search(root);
    printf("%s", "\n\n");

    MenuStart:
    puts("Menu:");
    puts("[1] Minimum");
    puts("[2] Maximum");
    puts("[3] Search item");
    puts("[4] Delete item");
    puts("[5] Insert item");
    puts("[0] Exit");
    scanf("%d", &menu_item);

    sales_order_detail_t item;
    tree_node_t *node = NULL;

    switch (menu_item)
    {
        case 1:
            node = min_item(root);
            if (node)
            {
                item = *node->sales_order_detail;
                print_data(item);
            }
            else
            {
                puts("ITEM NOT FOUND!");
            }
            break;

        case 2:
            node = max_item(root);
            if (node)
            {
                item = *node->sales_order_detail;
                print_data(item);
            }
            else
            {
                puts("ITEM NOT FOUND!");
            }
            break;

        case 3:
            switch (key)
            {
                case 1:
                    printf("Input sales order ID: ");
                    scanf("%d", &item.sales_order_ID);
                    break;

                case 2:
                    printf("Input sales order detail ID: ");
                    scanf("%d", &item.sales_order_detail_ID);
                    break;

                case 3:
                    printf("Input order quantity: ");
                    scanf("%d", &item.order_qty);
                    break;

                case 4:
                    printf("Input product ID: ");
                    scanf("%d", &item.product_ID);
                    break;

                case 5:
                    printf("Input unit price: ");
                    scanf("%f", &item.unit_price);
                    break;

                case 6:
                    printf("Input unit price discount: ");
                    scanf("%f", &item.unit_price_discount);
                    break;
            }

            node = search(root, item, cmp_f);
            if (node)
            {
                item = *node->sales_order_detail;
                print_data(item);
            }
            else
            {
                puts("ITEM NOT FOUND!");
            }
            break;

        case 4:
            switch (key)
            {
                case 1:
                    printf("Input sales order ID: ");
                    scanf("%d", &item.sales_order_ID);
                    break;

                case 2:
                    printf("Input sales order detail ID: ");
                    scanf("%d", &item.sales_order_detail_ID);
                    break;

                case 3:
                    printf("Input order quantity: ");
                    scanf("%d", &item.order_qty);
                    break;

                case 4:
                    printf("Input product ID: ");
                    scanf("%d", &item.product_ID);
                    break;

                case 5:
                    printf("Input unit price: ");
                    scanf("%f", &item.unit_price);
                    break;

                case 6:
                    printf("Input unit price discount: ");
                    scanf("%f", &item.unit_price_discount);
                    break;
            }

            node = search(root, item, cmp_f);
            if (node)
            {
                print_data(*node->sales_order_detail);
                delete_node(root, node);
                puts("Item deleted!");
            }
            else
            {
                puts("ITEM NOT FOUND!");
            }
            break;

        case 5:
            printf("Input sales order ID: ");
            scanf("%d", &item.sales_order_ID);
            printf("Input sales order detail ID: ");
            scanf("%d", &item.sales_order_detail_ID);
            printf("Input order quantity: ");
            scanf("%d", &item.order_qty);
            printf("Input product ID: ");
            scanf("%d", &item.product_ID);
            printf("Input unit price: ");
            scanf("%f", &item.unit_price);
            printf("Input unit price discount: ");
            scanf("%f", &item.unit_price_discount);
            insert_node(create_node(&item), &root, cmp_f);
            break;

        case 0:
            goto ProgramExitPoint;

    }
    goto MenuStart;


    ProgramExitPoint:
    free(sales_order_details);

    return 0;
}
