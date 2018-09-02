#ifndef IO_UNIT_H
#define IO_UNIT_H

int read_data(sales_order_detail_t **sales_order_details, int *n);

void print_data(sales_order_detail_t sales_order_detail);

int read_xml_item(FILE *f, char *xml_item);

int str_pos(const char *str, char c, int n);
int str_copy(const char *str1, char *str2, int n);

#endif // IO_UNIT_H
