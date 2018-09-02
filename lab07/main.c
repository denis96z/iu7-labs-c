#include <stdio.h>

#include "declarations.h"
#include "io_utils.h"
#include "token_utils.h"

// Максимальная длина имени файла.
#define MAX_FILE_NAME_LENGTH 255

// Точка входа программы.
int main(void)
{
    // Имя файла.
    char file_name[MAX_FILE_NAME_LENGTH];

    // Считываем имя файла.
    puts("Input file name:");
    printf("%c ", '>');
    // Проверяем ввод имени файла.
    if (!scanf("%s", file_name))
    {
        puts("\nIllegal expression.");
        return -1;
    }

    // Открываем файл.
    FILE *f = fopen(file_name, "r");
    if (!f)
    {
        puts("\nFile not found.");
        return -2;
    }

    // Таблица токенов.
    Token *tokens = NULL;
    int n = -1;

    // Читаем файл и получаем список токенов.
    read_tokens(f, &tokens, &n);
    fclose(f);

    find_keywords(tokens, n);

    f = fopen("out.xml", "w");
    print_tokens(f, tokens, n);
    puts("out.xml was created.");

    fclose(f);
    return 0;
}

