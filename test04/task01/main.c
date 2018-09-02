#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void print_f(char *f_string, ...)
{
    va_list arguments;
    va_start(arguments, f_string);

    for (int i = 0; i < strlen(f_string); i++)
    {
        switch (f_string[i])
        {
            case 'i':
                printf("%d", va_arg(arguments, int));
                break;

            case 'd':
                printf("%f", (float)va_arg(arguments, double));
                break;

            case 'c':
                printf("%c", (char)va_arg(arguments, int));
                break;

            case 's':
                printf("%s", va_arg(arguments, char*));
                break;

            default:
                printf("%c", ' ');
                break;
        }
    }

    va_end(arguments);
}

int main(void)
{
    print_f("d s r i   c", 0.05, "It's magic \n", 15, 't');
    return 0;
}
