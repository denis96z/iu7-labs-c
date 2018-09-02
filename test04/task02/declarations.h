#ifndef DECLARATIONS_H
#define DECLARATIONS_H

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

#endif // DECLARATIONS_H
