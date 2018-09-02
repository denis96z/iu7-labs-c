#ifndef IO_UNIT_H
#define IO_UNIT_H

typedef int (*print_data_t)(FILE *f);

typedef int (*modify_data_t)(void *data, database_t database);

int read_menu_item(int min, int max, int *menu_item);

int print_products(FILE *f);
int print_suppliers(FILE *f);
int print_shipments(FILE *f);

void print_product(product_t product);
void print_supplier(supplier_t supplier);
void print_shipment(shipment_t shipment);

int add_data(FILE *f, int size, database_t database);
int modify_data(FILE *f, int size, database_t database, modify_data_t modify_function);
int delete_data(void *data, database_t database);
int edit_data(void *data, database_t database);

int read_product_data(product_t *product);
int read_supplier_data(supplier_t *supplier);
int read_shipment_data(shipment_t *shipment);

int read_string(char *str, int max_length, const char *request, int *has_value);
int read_int(int *value, const int max_length, const char *request, int *has_value);
int read_float(float *value, const int max_length, const char *request, int *has_value);

#endif // IO_UNIT_H
