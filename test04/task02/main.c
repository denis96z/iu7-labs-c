#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <list.h>
#include "declarations.h"


int predicat(const product_t *item1, const char *color)
{
    if(!item1->has_color)
    {
        return 0;
    }
    return !strcmp(item1->color, color);
}


void print_product(product_t product)
{
    if (!product.exists)
    {
        return;
    }
    printf("| %*d ", MAX_ID_SYMBOLS, product.product_ID);
    printf("| %-*s ", MAX_PRODUCT_NAME_LENGTH, product.product_name);
    if (product.has_color)
    {
        printf("| %-*s ", MAX_COLOR_SYMBOLS, product.color);
    }
    else
    {
        printf("| %-*c ", MAX_COLOR_SYMBOLS, '-');
    }
    if (product.has_weight)
    {
        printf("| %*.*f ", MAX_FLOAT_SYMBOLS, MAX_FRACTION_SYMBOLS, product.weight);
    }
    else
    {
        printf("| %*c ", MAX_FLOAT_SYMBOLS, '-');
    }
    if (product.has_price)
    {
        printf("| %*.*f ", MAX_FLOAT_SYMBOLS, MAX_FRACTION_SYMBOLS, product.price);
    }
    else
    {
        printf("| %*c ", MAX_FLOAT_SYMBOLS, '-');
    }
    printf("| %-*s |\n", MAX_CITY_NAME_LENGTH, product.city);
}


struct data
{
    product_t product;
    struct list_head list;
};


int main(void)
{
    FILE *f = fopen("Products.dbf", "rb");

    LIST_HEAD(products_list);

    struct data *item;
    while (!feof(f))
    {
        product_t product;
        if (fread(&product, sizeof(product_t), 1, f) != 1)
        {
            break;
        }
        item = malloc(sizeof(*item));
        if (!item)
        {
            puts("MEMORY ERROR!");
            break;
        }
        item->product = product;

        list_add_tail(&item->list, &products_list);
    }

    /* Print */

    puts("Products:\n\n");
    struct list_head *iter;
    list_for_each(iter, &products_list)
    {
        item = list_entry(iter, struct data, list);
        print_product(item->product);
    }

    /* Compare predicat */

    char color[MAX_COLOR_SYMBOLS];
    puts("Input color: ");
    scanf("%s", color);

    puts("Specific products:\n\n");
    list_for_each(iter, &products_list)
    {
        item = list_entry(iter, struct data, list);
        if (predicat(&item->product, color))
        {
            print_product(item->product);
        }
    }

    /* Free */

    struct list_head *iter_safe;
    list_for_each_safe(iter, iter_safe, &products_list)
    {
        item = list_entry(iter, struct data, list);
        list_del(iter);
        free(item);
    }

    return 0;
}
