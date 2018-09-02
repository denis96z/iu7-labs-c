#ifndef IO_UTILS_H
#define IO_UTILS_H

// Функция считывания токенов из файла.
int read_tokens(FILE *f, Token **tokens_array, int *n);

int print_tokens(FILE *f, Token *tokens_array, int n);

#endif // IO_UTILS_H
