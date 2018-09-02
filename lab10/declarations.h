#ifndef DECLARATIONS_H
#define DECLARATIONS_H

typedef enum
{
    products_db,
    suppliers_db,
    shipments_db
} database_t;

#define MAX_PRODUCT_NAME_LENGTH 40
#define MAX_ID_SYMBOLS 11
#define MAX_COLOR_SYMBOLS 10
#define MAX_FLOAT_SYMBOLS 10
#define MAX_FRACTION_SYMBOLS 2

#define MAX_CITY_NAME_LENGTH 20

typedef float weight_t;
typedef float price_t;

typedef struct
{
    int exists;
    int product_ID;
    char product_name[MAX_PRODUCT_NAME_LENGTH];
    int has_color;
    char color[MAX_COLOR_SYMBOLS];
    int has_weight;
    weight_t weight;
    int has_price;
    price_t price;
    char city[MAX_CITY_NAME_LENGTH];
} product_t;

#define MAX_SUPPLIER_NAME_LENGTH 50
#define MAX_STATUS_SYMBOLS 6

#define AVERAGE_STATUS 50

typedef struct
{
    int exists;
    int supplier_ID;
    char supplier_name[MAX_SUPPLIER_NAME_LENGTH];
    int status;
    char city[MAX_CITY_NAME_LENGTH];
} supplier_t;

#define MAX_QTY_SYMBOLS 8

typedef struct
{
    int exists;
    int shipment_ID;
    int supplier_ID;
    int product_ID;
    int qty;
} shipment_t;

#endif // DECLARATIONS_H
