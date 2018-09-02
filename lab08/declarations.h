#ifndef DECLARATIONS_H
#define DECLARATIONS_H

typedef enum
{
    variable,
    constant,
    operation,
    function
} token_t;

typedef struct
{
    char *name;
    token_t type;
    double value;
} token_struct_t;

#define MAX_NAME_LENGTH 255
typedef struct
{
    char name[MAX_NAME_LENGTH];
    double value;
} variable_t;

#endif // DECLARATIONS_H
