#include <stdio.h>

#include "declarations.h"
#include "io_unit.h"
#include "task_solution.h"

int main(void)
{
    // Файлы баз данных.
    FILE *f_products = fopen("Products.dbf", "rb+");
    FILE *f_suppliers = fopen("Suppliers.dbf", "rb+");
    FILE *f_shipments = fopen("Shipments.dbf", "rb+");

    if (!f_products || !f_suppliers || !f_shipments)
    {
        puts ("CANNOT OPEN DATABASE!");
        return 1;
    }

    // Указатели на выбранные файлы и действия для них.
    FILE *f;
    print_data_t print_data;
    int size;
    database_t database;
    task_solution_t task_solution;

    // Выбранный пункт главного меню.
    int main_menu_item = 0;
    // Выбранная база данных.
    int selected_database = 0;
    // Выбранная задача.
    int selected_task = 1;

    MainMenu:
    f_products = fopen("Products.dbf", "rb+");
    f_suppliers = fopen("Suppliers.dbf", "rb+");
    f_shipments = fopen("Shipments.dbf", "rb+");

    puts("Select operation:");
    puts("[1] Print data");
    puts("[2] Add data");
    puts("[3] Edit data");
    puts("[4] Delete data");
    puts("[5] Find solution");
    puts("[-1] Exit");
    if (!read_menu_item(-1, 5, &main_menu_item) || !main_menu_item)
    {
        puts("ITEM NOT FOUND! REPEAT INPUT.");
        goto MainMenu;
    }
    if (main_menu_item == -1)
    {
        goto ProgramExitPoint;
    }
    if (main_menu_item == 5)
    {
        goto TaskSolutionMenu;
    }

    SubMenu:
    puts("Select database:");
    puts("[1] Products");
    puts("[2] Suppliers");
    puts("[3] Shipments");
    if (!read_menu_item(1, 3, &selected_database))
    {
        puts("ITEM NOT FOUND! REPEAT INPUT.");
        goto SubMenu;
    }
    goto Procedures;

    TaskSolutionMenu:
    puts("Select task:");
    puts("[1] Find suppliers for each product");
    puts("[2] Find suppliers by product ID");
    puts("[3] Find suppliers who do not supply products");
    puts("[4] Find suppliers who supply products of a particular color");
    puts("[5] Find products that are supplied by suppliers whose status is greater than average");
    if (!read_menu_item(1, 5, &selected_task))
    {
        puts("ITEM NOT FOUND! REPEAT INPUT.");
        goto TaskSolutionMenu;
    }
    switch (selected_task)
    {
        case 1:
            task_solution = task1_solution;
            break;

        case 2:
            task_solution = task2_solution;
            break;

        case 3:
            task_solution = task3_solution;
            break;

        case 4:
            task_solution = task4_solution;
            break;

        case 5:
            task_solution = task5_solution;
            break;
    }
    goto TaskSelectedPoint;

    Procedures:
    switch (selected_database)
    {
        case 1:
            f = f_products;
            print_data = print_products;
            database = products_db;
            size = sizeof(product_t);
            break;

        case 2:
            f = f_suppliers;
            print_data = print_suppliers;
            database = suppliers_db;
            size = sizeof(supplier_t);
            break;

        case 3:
            f = f_shipments;
            print_data = print_shipments;
            database = shipments_db;
            size = sizeof(shipment_t);
            break;
    }

    TaskSelectedPoint:
    switch (main_menu_item)
    {
        case 1:
            if (!print_data(f))
            {
                goto ProgramExitPoint;
            }
            break;

        case 2:
            if (!add_data(f, size, database))
            {
                goto ProgramExitPoint;
            }
            break;

        case 3:
            if (!modify_data(f, size, database, edit_data))
            {
                goto ProgramExitPoint;
            }
            break;

        case 4:
            if (!modify_data(f, size, database, delete_data))
            {
                goto ProgramExitPoint;
            }
            break;

        case 5:
            if (!task_solution(f_products, f_suppliers, f_shipments))
            {
                goto ProgramExitPoint;
            }
            break;
    }

    fclose(f_products);
    fclose(f_suppliers);
    fclose(f_shipments);

    goto MainMenu;

    ProgramExitPoint:

    if (f_products)
    {
        fclose(f_products);
    }
    if (f_suppliers)
    {
        fclose(f_suppliers);
    }
    if (f_shipments)
    {
        fclose(f_shipments);
    }

    return 0;
}
