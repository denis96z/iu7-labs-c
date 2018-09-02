#ifndef TOKEN_UTILS_H
#define TOKEN_UTILS_H

// Приращение количества элементов массива.
#define TOKENS_ARRAY_INCREMENT 50

// Количество букв.
#define LETTERS_NUM 53
// Количество цифр.
#define DIGITS_NUM 10
// Количество знаков.
#define SIGNS_NUM 23

// Возможные состояния автомата.
typedef enum
{
    initial,
    variable,
    digit_constant,
    punctuators,
    compiler_directive,
    single_line_comment,
    multiline_comment,
    string,
    char_literal
} State;

// Буквы.
extern const char letters[LETTERS_NUM];
// Цифры.
extern const char digits[DIGITS_NUM];
// Знаки.
extern const char signs[SIGNS_NUM];

// Функция проверки принадлежности символа массиву.
int contains(char c, const char *symbols, int n);

int add_token(char *token, Token** tokens_array, int *length, int line,
              int column, int *n, int *array_size, TokenCategories category);

int find_keywords(Token *tokens_array, int n);

#endif // TOKEN_UTILS_H
