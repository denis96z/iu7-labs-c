#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <stdio.h>

#include "declarations.h"
#include "token_utils.h"

#define TOKENS_ARRAY_LENGTH_INCREMENT 100

#define KEYWORDS_NUM 37

// Буквы.
const char letters[LETTERS_NUM] =
{
    'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L',
    'M', 'N', 'O', 'P', 'Q', 'R',
    'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd',
    'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '_'
};

// Цифры.
const char digits[DIGITS_NUM] =
{
    '0', '1', '2', '3', '4', '5', '6' ,'7', '8', '9'
};

// Знаки.
const char signs[SIGNS_NUM] =
{
    '[', ']', '(', ')', '{', '}',
    '+', '-', '<', '>', '&', '*',
    '/', '%', '=', '!', '^', '|',
    '?', ':', ';', '.', '#'
};

// Функция проверки принадлежности символа массиву.
int contains(char c, const char *symbols, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (c == symbols[i])
        {
            return 1;
        }
    }
    return 0;
}

Token* set_length(Token *tokens_array, int n)
{
    tokens_array = (Token*)realloc(tokens_array, n * sizeof(Token));
    return tokens_array;
}

int add_token(char *token, Token** tokens_array, int *length, int line,
              int column, int *n, int *array_size, TokenCategories category)
{
    (*n)++;
    if ((*n) == (*array_size))
    {
        *array_size += TOKENS_ARRAY_LENGTH_INCREMENT;
        *tokens_array = set_length(*tokens_array, *array_size);
        assert(*tokens_array);
    }

    for (int i = 0; i <= (*length); i++)
    {
        (*tokens_array)[*n].token_name[i] = token[i];
    }
    (*tokens_array)[*n].token_name_length = *length;
    (*tokens_array)[*n].column = column;
    (*tokens_array)[*n].line = line;
    (*tokens_array)[*n].category = category;

    *length = 0;
    token[0] = '\0';

    return 0;
}

const char keywords[KEYWORDS_NUM][10] =
{
    "auto", "break", "case", "char", "const",
    "continue", "default", "do", "double", "else",
    "enum", "extern", "float", "for", "goto", "if",
    "inline", "int", "long", "register", "restrict",
    "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned",
    "void", "volatile", "while", "_Bool", "_Complex",
    "_Imaginary"
};


int find_keywords(Token *tokens_array, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (tokens_array[i].category == identifier)
        {
            for (int j = 0; j < KEYWORDS_NUM; j++)
            {
                if (strcmp(tokens_array[i].token_name, keywords[j]) == 0)
                {
                    tokens_array[i].category = keyword;
                    break;
                }
            }
        }
    }

    return 0;
}
