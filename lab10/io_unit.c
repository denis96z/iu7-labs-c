#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include "declarations.h"
#include "io_unit.h"


int read_menu_item(int min, int max, int *menu_item)
{
    char console_string[3];

    printf("%c ", '>');
    rewind(stdin);
    scanf("%3s", console_string);
    *menu_item = atoi(console_string);

    if ((*menu_item < min) || (*menu_item > max))
    {
        return 0;
    }

    return 1;
}


int print_products(FILE *f)
{
    assert (f);

    rewind(f);

    // Продукт.
    product_t product;
    // Количество продуктов в базе.
    int n = 0;

    // Читаем данные из файла и печатаем в таблицу.
    const int table_width = MAX_ID_SYMBOLS + MAX_PRODUCT_NAME_LENGTH + MAX_COLOR_SYMBOLS +
        MAX_FLOAT_SYMBOLS + MAX_FLOAT_SYMBOLS + MAX_CITY_NAME_LENGTH + 19;
    for (int i = 0; i < table_width; i++)
    {
        printf("%c", '-');
    }
    puts("");
    printf("| %-*s ", MAX_ID_SYMBOLS, "Product ID");
    printf("| %-*s ", MAX_PRODUCT_NAME_LENGTH, "Product Name");
    printf("| %-*s ", MAX_COLOR_SYMBOLS, "Color");
    printf("| %-*s ", MAX_FLOAT_SYMBOLS, "Weight");
    printf("| %-*s ", MAX_FLOAT_SYMBOLS, "Price");
    printf("| %-*s |\n", MAX_CITY_NAME_LENGTH, "City");
    for (int i = 0; i < table_width; i++)
    {
        printf("%c", '-');
    }
    puts("");

    while (!feof(f))
    {
        if (fread(&product, sizeof(product_t), 1, f) != 1)
        {
            break;
        }
        print_product(product);
        n++;
    }
    if (n == 0)
    {
        puts("DATABASE IS EMPTY!");
    }
    for (int i = 0; i < table_width; i++)
    {
        printf("%c", '-');
    }
    puts("\n");

    return 1;
}


int print_suppliers(FILE *f)
{
    assert (f);

    rewind(f);

    // Поставщик.
    supplier_t supplier;
    // Количество поставщиков в базе.
    int n = 0;

    // Читаем данные из файла и печатаем в таблицу.
    const int table_width = MAX_ID_SYMBOLS + MAX_SUPPLIER_NAME_LENGTH + MAX_STATUS_SYMBOLS +
        MAX_CITY_NAME_LENGTH + 13;
    for (int i = 0; i < table_width; i++)
    {
        printf("%c", '-');
    }
    puts("");
    printf("| %-*s ", MAX_ID_SYMBOLS, "Supplier ID");
    printf("| %-*s ", MAX_SUPPLIER_NAME_LENGTH, "Supplier Name");
    printf("| %-*s ", MAX_STATUS_SYMBOLS, "Status");
    printf("| %-*s |\n", MAX_CITY_NAME_LENGTH, "City");
    for (int i = 0; i < table_width; i++)
    {
        printf("%c", '-');
    }
    puts("");

    while (!feof(f))
    {
        if (fread(&supplier, sizeof(supplier_t), 1, f) != 1)
        {
            break;
        }
        print_supplier(supplier);
        n++;
    }
    if (n == 0)
    {
        puts("DATABASE IS EMPTY!");
    }
    for (int i = 0; i < table_width; i++)
    {
        printf("%c", '-');
    }
    puts("\n");

    return 1;
}


int print_shipments(FILE *f)
{
    assert (f);

    rewind(f);

    // Продукт.
    shipment_t shipment;
    int n = 0;

    // Читаем данные из файла и печатаем в таблицу.
    const int table_width = MAX_ID_SYMBOLS + MAX_ID_SYMBOLS + MAX_ID_SYMBOLS +
        MAX_QTY_SYMBOLS + 13;
    for (int i = 0; i < table_width; i++)
    {
        printf("%c", '-');
    }
    puts("");
    printf("| %-*s ", MAX_ID_SYMBOLS, "Shipment ID");
    printf("| %-*s ", MAX_ID_SYMBOLS, "Supplier ID");
    printf("| %-*s ", MAX_ID_SYMBOLS, "Product ID");
    printf("| %-*s |\n", MAX_QTY_SYMBOLS, "Quantity");
    for (int i = 0; i < table_width; i++)
    {
        printf("%c", '-');
    }
    puts("");

    while (!feof(f))
    {
        if (fread(&shipment, sizeof(shipment_t), 1, f) != 1)
        {
            break;
        }
        print_shipment(shipment);
        n++;
    }
    if (n == 0)
    {
        puts("DATABASE IS EMPTY!");
    }
    for (int i = 0; i < table_width; i++)
    {
        printf("%c", '-');
    }
    puts("\n");

    return 1;
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


void print_supplier(supplier_t supplier)
{
    if (!supplier.exists)
    {
        return;
    }
    printf("| %*d ", MAX_ID_SYMBOLS, supplier.supplier_ID);
    printf("| %-*s ", MAX_SUPPLIER_NAME_LENGTH, supplier.supplier_name);
    printf("| %*d ", MAX_STATUS_SYMBOLS, supplier.status);
    printf("| %-*s |\n", MAX_CITY_NAME_LENGTH, supplier.city);
}


void print_shipment(shipment_t shipment)
{
    if (!shipment.exists)
    {
        return;
    }
    printf("| %*d ", MAX_ID_SYMBOLS, shipment.shipment_ID);
    printf("| %*d ", MAX_ID_SYMBOLS, shipment.supplier_ID);
    printf("| %*d ", MAX_ID_SYMBOLS, shipment.product_ID);
    printf("| %*d |\n", MAX_QTY_SYMBOLS, shipment.qty);
}


int add_data(FILE *f, int size, database_t database)
{
    assert(f);

    rewind(f);

    // Считываемые из файла данные.
    void *data = malloc(size);
    if (!data)
    {
        puts("MEMORY ACCESS ERROR!");
        return 0;
    }

    // Количество записей в базе данных.
    int n = 0;

    // Считываем все записи и считаем их количество.
    while (!feof(f))
    {
        if (fread(data, size, 1, f) == 1)
        {
            n++;
        }
    }

    // Вводим данные.
    switch (database)
    {
        case products_db:
            {
                product_t *product = (product_t*)data;
                if (n > 0)
                {
                    product->product_ID++;
                }
                else
                {
                    product->product_ID = 1;
                }
                if (!read_product_data(product))
                {
                    puts("ERROR READING DATA!");
                    return 0;
                }
                data = product;
            }
            break;

        case suppliers_db:
            {
                supplier_t *supplier = (supplier_t*)data;
                if (n > 0)
                {
                    supplier->supplier_ID++;
                }
                else
                {
                    supplier->supplier_ID = 1;
                }

                if (!read_supplier_data(supplier))
                {
                    puts("ERROR READING DATA!");
                    return 0;
                }
                data = supplier;
            }
            break;

        case shipments_db:
            {
                shipment_t *shipment = (shipment_t*)data;
                if (n > 0)
                {
                    shipment->shipment_ID++;
                }
                else
                {
                    shipment->shipment_ID = 1;
                }

                if (!read_shipment_data(shipment))
                {
                    puts("ERROR READING DATA!");
                    return 0;
                }
            }
            break;
    }

    if (fwrite(data, size, 1, f) != 1)
    {
        puts("FILE OPERATION ERROR");
        return 0;
    }

    free(data);

    return 1;
}


int modify_data(FILE *f, int size, database_t database, modify_data_t modify_function)
{
    assert(f);

    rewind(f);

    // Узнаем ID для поиска.
    int ID = 0;
    {
        int has_value = 0;
        if (!read_int(&ID, MAX_ID_SYMBOLS, "Input ID:", &has_value))
        {
            puts("INPUT ERROR!");
            return 0;
        }
    }

    // Считываемые из файла данные.
    void *data = malloc(size);
    if (!data)
    {
        puts("MEMORY ACCESS ERROR!");
        return 0;
    }

    while (!feof(f))
    {
        if (fread(data, size, 1, f) == 1)
        {
            switch (database)
            {

                case products_db:
                    {
                        // Продукт.
                        product_t *product = (product_t*)data;

                        // Если ID не совпадает продолжаем считывать данные.
                        if ((product->product_ID != ID) || (!product->exists))
                        {
                            continue;
                        }

                        puts("Item found:");
                        print_product(*product);
                    }
                    break;

                case suppliers_db:
                    {
                        // Поставщик.
                        supplier_t *supplier = (supplier_t*)data;

                        // Если ID не совпадает продолжаем считывать данные.
                        if ((supplier->supplier_ID != ID) || (!supplier->exists))
                        {
                            continue;
                        }

                        puts("Item found:");
                        print_supplier(*supplier);
                    }
                    break;

                case shipments_db:
                    {
                        // Поставка.
                        shipment_t *shipment = (shipment_t*)data;

                        // Если ID не совпадает продолжаем считывать данные.
                        if ((shipment->shipment_ID != ID) || (!shipment->exists))
                        {
                            continue;
                        }

                        puts("Item found:");
                        print_shipment(*shipment);
                    }
                    break;
            }
            modify_function(data, database);
            // Ищем позицию в файле и перезаписываем элемент, выходим из цикла.
            fseek(f, ((ftell(f) / size) - 1) * size, SEEK_SET);
            if (fwrite(data, size, 1, f) != 1)
            {
                puts("FILE OPERATION ERROR");
                return 0;
            }
            return 1;
        }
    }

    // Если прочитали весь файл, значит элемент в файле отсутствует.
    puts("ITEM WITH CURRENT ID NOT FOUND!");

    free(data);

    return 1;
}


int delete_data(void *data, database_t database)
{
    switch(database)
    {
        case products_db:
            {
                // Продукт.
                product_t *product = (product_t*)data;
                product->exists = 0;
            }
            break;

        case suppliers_db:
            {
                // Поставщик.
                supplier_t *supplier = (supplier_t*)data;
                supplier->exists = 0;
            }
            break;

        case shipments_db:
            {
                // Поставка.
                shipment_t *shipment = (shipment_t*)data;
                shipment->exists = 0;
            }
            break;
    }

    return 1;
}


int edit_data(void *data, database_t database)
{
    switch (database)
    {
        case products_db:
            {
                // Продукт.
                product_t *product = (product_t*)data;
                if (!read_product_data(product))
                {
                    puts("ERROR READING DATA!");
                    return 0;
                }
            }
            break;

        case suppliers_db:
            {
                // Поставщик.
                supplier_t *supplier = (supplier_t*)data;
                if (!read_supplier_data(supplier))
                {
                    puts("ERROR READING DATA!");
                    return 0;
                }
            }
            break;

        case shipments_db:
            {
                // Поставка.
                shipment_t *shipment = (shipment_t*)data;
                if (!read_shipment_data(shipment))
                {
                    puts("ERROR READING DATA!");
                    return 0;
                }
            }
            break;
    }

    return 1;
}


int read_product_data(product_t *product)
{
    // Продукт не удален из базы.
    product->exists = 1;

    int has_value = 1;

    if (!read_string(product->product_name, MAX_PRODUCT_NAME_LENGTH, "Product name:", &has_value))
    {
        puts("INPUT ERROR!");
        return 0;
    }

    if (!read_string(product->color, MAX_COLOR_SYMBOLS, "Color:", &product->has_color))
    {
        puts("INPUT ERROR!");
        return 0;
    }

    if (!read_float(&product->weight, MAX_FLOAT_SYMBOLS, "Weight:", &product->has_weight))
    {
        puts("INPUT ERROR!");
        return 0;
    }

    if (!read_float(&product->price, MAX_FLOAT_SYMBOLS, "Price:", &product->has_price))
    {
        puts("INPUT ERROR!");
        return 0;
    }

    if (!read_string(product->city, MAX_CITY_NAME_LENGTH, "City:", &has_value))
    {
        puts("INPUT ERROR!");
        return 0;
    }

    return 1;
}


int read_supplier_data(supplier_t *supplier)
{
    // Поставщик не удален из базы.
    supplier->exists = 1;

    int has_value = 1;

    if (!read_string(supplier->supplier_name, MAX_SUPPLIER_NAME_LENGTH, "Supplier name:", &has_value))
    {
        puts("INPUT ERROR!");
        return 0;
    }

    if (!read_int(&supplier->status, MAX_STATUS_SYMBOLS, "Status:", &has_value))
    {
        puts("INPUT ERROR!");
        return 0;
    }


    if (!read_string(supplier->city, MAX_CITY_NAME_LENGTH, "City:", &has_value))
    {
        puts("INPUT ERROR!");
        return 0;
    }

    return 1;
}


int read_shipment_data(shipment_t *shipment)
{
    // Поставка не удалена из базы.
    shipment->exists = 1;

    int has_value = 1;

    if (!read_int(&shipment->product_ID, MAX_ID_SYMBOLS, "Product ID:", &has_value))
    {
        puts("INPUT ERROR!");
        return 0;
    }


    if (!read_int(&shipment->supplier_ID, MAX_ID_SYMBOLS, "Supplier ID:", &has_value))
    {
        puts("INPUT ERROR!");
        return 0;
    }

    if (!read_int(&shipment->qty, MAX_QTY_SYMBOLS, "Quantity:", &has_value))
    {
        puts("INPUT ERROR!");
        return 0;
    }

    return 1;
}


int read_string(char *str, int max_length, const char *request, int *has_value)
{
    Input:
    puts(request);
    printf("%c ", '>');
    rewind(stdin);
    // Считываем поле.
    if (fgets(str, max_length, stdin) == NULL)
    {
        puts("INPUT ERROR! REPEAT INPUT.");
        goto Input;
    }
    else
    {
        // Если длина менее двух символов, значение недопустимое, повторяем ввод.
        int length = strlen(str);
        if (length < 2)
        {
            puts("INVALID VALUE! REPEAT INPUT.");
            goto Input;
        }
        // Удаляем символ новой строки.
        str[length - 1] = '\0';
    }
    // Если первый символ "-", значит значение отсутствует.
    if (strncmp(str, "-", 1) == 0)
    {
        *has_value = 0;
    }
    else
    {
        *has_value = 1;
    }

    return 1;
}


int read_int(int *value, const int max_length, const char *request, int *has_value)
{
    // Вводимая строка.
    char str[max_length];

    Input:
    puts(request);
    printf("%c ", '>');
    rewind(stdin);
    // Считываем значение.
    if (fgets(str, max_length, stdin) == NULL)
    {
        puts("INPUT ERROR! REPEAT INPUT.");
        goto Input;
    }
    else
    {
        // Если длина менее двух символов, значение недопустимое, повторяем ввод.
        int length = strlen(str);
        if (length < 2)
        {
            puts("INVALID VALUE! REPEAT INPUT.");
            goto Input;
        }
        // Удаляем символ новой строки.
        str[length - 1] = '\0';
    }
    // Если первый символ "-", значит значение отсутствует.
    if (strncmp(str, "-", 1) == 0)
    {
        *has_value = 0;
    }
    else
    {
        // Пытаемся перевести строку в число.
        *value = atoi(str);
        if (errno == ERANGE)
        {
            puts("INVALID VALUE! REPEAT INPUT.");
            errno = 0;
            goto Input;
        }
        *has_value = 1;
    }

    return 1;
}


int read_float(float *value, const int max_length, const char *request, int *has_value)
{
    // Вводимая строка.
    char str[max_length];

    Input:
    puts(request);
    printf("%c ", '>');
    rewind(stdin);
    // Считываем значение.
    if (fgets(str, max_length, stdin) == NULL)
    {
        puts("INPUT ERROR! REPEAT INPUT.");
        goto Input;
    }
    else
    {
        // Если длина менее двух символов, значение недопустимое, повторяем ввод.
        int length = strlen(str);
        if (length < 2)
        {
            puts("INVALID VALUE! REPEAT INPUT.");
            goto Input;
        }
        // Удаляем символ новой строки.
        str[length - 1] = '\0';
    }
    // Если первый символ "-", значит значение отсутствует.
    if (strncmp(str, "-", 1) == 0)
    {
        *has_value = 0;
    }
    else
    {
        // Пытаемся перевести строку в число.
        *value = (float)atof(str);
        if (errno == ERANGE)
        {
            puts("INVALID VALUE! REPEAT INPUT.");
            errno = 0;
            goto Input;
        }
        *has_value = 1;
    }

    return 1;
}
