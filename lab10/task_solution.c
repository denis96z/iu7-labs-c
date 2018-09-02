#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "declarations.h"
#include "io_unit.h"
#include "task_solution.h"


int task1_solution(FILE *f_products, FILE *f_suppliers, FILE *f_shipments)
{
    assert(f_products && f_suppliers && f_shipments);

    // Продукт.
    product_t product;
    // Размер структуры product_t.
    int product_size = sizeof(product_t);
    // Поставщик.
    supplier_t supplier;
    // Размер структуры supplier_t.
    int supplier_size = sizeof(supplier_t);
    // Поставка.
    shipment_t shipment;
    // Размер структуры shipment_t.
    int shipment_size = sizeof(shipment_t);
    // Количество поставщиков каждого продукта.
    int n;

    rewind(f_products);
    // Читаем все данные о продуктах.
    while (!feof(f_products))
    {
        if ((fread(&product, product_size, 1, f_products) == 1) && product.exists)
        {
            printf("%s:\n", product.product_name);
            rewind(f_shipments);
            n = 0;
            // Ищем поставки для каждого продукта.
            while (!feof(f_shipments))
            {
                if ((fread(&shipment, shipment_size, 1, f_shipments) == 1) && shipment.exists)
                {
                    if (product.product_ID != shipment.product_ID)
                    {
                        continue;
                    }
                    rewind(f_suppliers);
                    // Ищем поставщика и печатаем данные.
                    while (!feof(f_suppliers))
                    {
                        if ((fread(&supplier, supplier_size, 1, f_suppliers) == 1) && supplier.exists)
                        {
                            if (shipment.supplier_ID != supplier.supplier_ID)
                            {
                                continue;
                            }
                            n++;
                            printf("%d. %s\n", n, supplier.supplier_name);
                        }
                    }
                }
            }
            if (n == 0)
            {
                puts("NO SUPPLIERS SUPPLY THIS PRODUCT!");
            }
            printf("%c", '\n');
        }
    }

    return 1;
}


int task2_solution(FILE *f_products, FILE *f_suppliers, FILE *f_shipments)
{
    assert(f_products && f_suppliers && f_shipments);

    // ID продукта.
    int product_ID;

    // Запрашиваем ID.
    {
        int has_value = 1;
        if (!read_int(&product_ID, MAX_ID_SYMBOLS, "Product ID:", &has_value))
        {
            puts("INPUT ERROR!");
            return 0;
        }
    }

    // Продукт.
    product_t product;
    // Размер структуры product_t.
    int product_size = sizeof(product_t);
    // Поставщик.
    supplier_t supplier;
    // Размер структуры supplier_t.
    int supplier_size = sizeof(supplier_t);
    // Поставка.
    shipment_t shipment;
    // Размер структуры shipment_t.
    int shipment_size = sizeof(shipment_t);

    rewind(f_products);
    rewind(f_shipments);

    // Количество поставщиков продукта.
    int suppliers_found = 0;

    // Ищем продукт с указанным ID.
    while (!feof(f_products))
    {
        if ((fread(&product, product_size, 1, f_products) == 1) && product.exists)
        {
            if (product_ID != product.product_ID)
            {
                continue;
            }
            printf("%s:\n", product.product_name);
            // Ищем все поставки продукта.
            while (!feof(f_shipments))
            {
                if ((fread(&shipment, shipment_size, 1, f_shipments) == 1) && shipment.exists)
                {
                    if (product.product_ID != shipment.product_ID)
                    {
                        continue;
                    }
                    rewind(f_suppliers);
                    // Ищем поставщиков.
                    while (!feof(f_suppliers))
                    {
                        if ((fread(&supplier, supplier_size, 1, f_suppliers) == 1) && supplier.exists)
                        {
                            if (shipment.supplier_ID != supplier.supplier_ID)
                            {
                                continue;
                            }
                            suppliers_found++;
                            printf("%d. %s\n", suppliers_found, supplier.supplier_name);
                        }
                    }
                }
            }
            break;
        }
    }
    if (!suppliers_found)
    {
        puts("NO SUPPLIERS SUPPLY THIS PRODUCT!");
    }
    printf("%c", '\n');

    return 1;
}


int task3_solution(FILE *f_products, FILE *f_suppliers, FILE *f_shipments)
{
    assert(f_products && f_suppliers && f_shipments);

    // Поставщик.
    supplier_t supplier;
    // Размер структуры supplier_t.
    int supplier_size = sizeof(supplier_t);
    // Поставка.
    shipment_t shipment;
    // Размер структуры shipment_t.
    int shipment_size = sizeof(shipment_t);

    // Количество поставщиков, не поставляющих никакие продукты.
    int supplier_number = 0;

    // Показатель, поставляет ли товары поставщик.
    int n;

    rewind (f_suppliers);

    // Просматриваем всех поставщиков.
    while (!feof(f_suppliers))
    {
        if ((fread(&supplier, supplier_size, 1, f_suppliers) == 1) && supplier.exists)
        {
            rewind(f_shipments);
            n = 0;
            // Просматриваем все поставки. Определяем, есть ли товары данного поставщика.
            while (!feof(f_shipments))
            {
                if ((fread(&shipment, shipment_size, 1, f_shipments) == 1) && shipment.exists)
                {
                    if (supplier.supplier_ID != shipment.supplier_ID)
                    {
                        continue;
                    }
                    n = 1;
                }
            }
            // Если поставщик ничего не поставляет, печатаем его.
            if (n == 0)
            {
                supplier_number++;
                printf("%d. %s\n", supplier_number, supplier.supplier_name);
            }
        }
    }
    if (supplier_number == 0)
    {
        puts("SUPPLIERS WHO SUPPLY NOTHING NOT FOUND!");
    }
    printf("%c", '\n');

    return 1;
}


int task4_solution(FILE *f_products, FILE *f_suppliers, FILE *f_shipments)
{
    assert(f_products && f_suppliers && f_shipments);

    // Цвет продукта.
    char color[MAX_COLOR_SYMBOLS];
    // Запрашиваем цвет продукта.
    {
        int has_value = 1;
        if (!read_string(color, MAX_COLOR_SYMBOLS, "Color:", &has_value))
        {
            puts("INPUT ERROR!");
            return 0;
        }
    }

    // Продукт.
    product_t product;
    // Размер структуры product_t.
    int product_size = sizeof(product_t);
    // Поставщик.
    supplier_t supplier;
    // Размер структуры supplier_t.
    int supplier_size = sizeof(supplier_t);
    // Поставка.
    shipment_t shipment;
    // Размер структуры shipment_t.
    int shipment_size = sizeof(shipment_t);

    int n_products = 0;
    int n_suppliers = 0;

    rewind(f_products);
    // Читаем все данные о продуктах.
    while (!feof(f_products))
    {
        if ((fread(&product, product_size, 1, f_products) == 1) && product.exists)
        {
            // Ищем продукты с заданным цветом.
            if (strcmp(color, product.color) != 0)
            {
                continue;
            }
            n_products++;
            rewind(f_shipments);
            // Ищем поставки для найденных продуктов.
            while (!feof(f_shipments))
            {
                if ((fread(&shipment, shipment_size, 1, f_shipments) == 1) && shipment.exists)
                {
                    if (product.product_ID != shipment.product_ID)
                    {
                        continue;
                    }
                    rewind(f_suppliers);
                    // Ищем поставщика и печатаем данные.
                    while (!feof(f_suppliers))
                    {
                        if ((fread(&supplier, supplier_size, 1, f_suppliers) == 1) && supplier.exists)
                        {
                            if (shipment.supplier_ID != supplier.supplier_ID)
                            {
                                continue;
                            }
                            n_suppliers++;
                            printf("%d. %s\n", n_suppliers, product.product_name);
                            printf("%d. %s\n\n", n_suppliers, supplier.supplier_name);
                        }
                    }
                }
            }
        }
    }

    // Проверяем, найдены ли продукты указанного цвета и поставщики, поставляющие данные продукты.
    if (!n_products)
    {
        puts("NO PRODUTS OF THIS COLOR FOUND!");
    }
    if (!n_suppliers)
    {
        puts("NO SUPPLIERS OF PRODUCTS OF THIS COLOR FOUND!");
    }
    printf("%c", '\n');


    return 1;
}


int task5_solution(FILE *f_products, FILE *f_suppliers, FILE *f_shipments)
{
    assert(f_products && f_suppliers && f_shipments);

    // Продукт.
    product_t product;
    // Размер структуры product_t.
    int product_size = sizeof(product_t);
    // Поставщик.
    supplier_t supplier;
    // Размер структуры supplier_t.
    int supplier_size = sizeof(supplier_t);
    // Поставка.
    shipment_t shipment;
    // Размер структуры shipment_t.
    int shipment_size = sizeof(shipment_t);

    int n_suppliers = 0;
    int n_products;

    rewind(f_products);
    // Читаем все данные о поставщиках.
    while (!feof(f_suppliers))
    {
        if ((fread(&supplier, supplier_size, 1, f_suppliers) == 1) && supplier.exists)
        {
            // Ищем поставщиков, статус которых больше среднего.
            if (supplier.status <= AVERAGE_STATUS)
            {
                continue;
            }
            n_suppliers++;
            printf("Supplier: %s\n", supplier.supplier_name);
            printf("Status: %d\n", supplier.status);
            puts("Products:");
            rewind(f_shipments);
            n_products = 0;
            // Ищем поставки найденных поставщиков.
            while (!feof(f_shipments))
            {
                if ((fread(&shipment, shipment_size, 1, f_shipments) == 1) && shipment.exists)
                {
                    if (supplier.supplier_ID != shipment.supplier_ID)
                    {
                        continue;
                    }
                    rewind(f_products);
                    // Ищем продукты и печатаем данные.
                    while (!feof(f_products))
                    {
                        if ((fread(&product, product_size, 1, f_products) == 1) && product.exists)
                        {
                            if (shipment.product_ID != product.product_ID)
                            {
                                continue;
                            }
                            n_products++;
                            printf("%d. %s\n", n_products, product.product_name);
                        }
                    }
                }
            }
            if (!n_products)
            {
                puts("THIS SUPPLIER SUPPLIES NO PRODUCTS!");
            }
            printf("%c", '\n');
        }
    }

    if (!n_suppliers)
    {
        puts("NO SUPPLIERS WITH STATUS GREATER THAN AVERAGE!");
    }
    printf("%c", '\n');

    return 1;
}
