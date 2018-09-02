#ifndef DECLARATIONS_H
#define DECLARATIONS_H

// Категории токенов.
typedef enum
{
    keyword,
    identifier,
    constant,
    string_literal,
    punctuator
} TokenCategories;

// Максимальная длина токена.
#define MAX_TOKEN_LENGTH 255

// Тип "токен".
typedef struct
{
    TokenCategories category;
    char token_name[MAX_TOKEN_LENGTH];
    unsigned int line;
    unsigned int column;
    int token_name_length;
} Token;

#endif // DECLARATIONS_H
