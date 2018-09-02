#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "string_utils.h"

int is_int(const char *str)
{
    // Длина строки.
    int length = strlen(str);

    // Проверяем, является ли каждый символ цифрой.
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
    }

    return 1;
}

int copy_str(const char *str1, int index, int length, char *str2)
{
    // Индекс последнего копируемого символа.
    int p = index + length;

    // Текущая позиция в изменяемой строке.
    int j = 0;

    for (int i = index; i < p; i++)
    {
        str2[j++] = str1[i];
    }
    str2[j] = '\0';

    return 1;
}
