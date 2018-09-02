#ifndef XML_UTILS_H
#define XML_UTILS_H

int readTable(FILE *f, SalesOrderDetail **table, int *n);

bool parseString(char *str);

#endif // XML_UTILS_H
