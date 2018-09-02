#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declarations.h"
#include "io_utils.h"

int main(int argc, char **argv)
{
    // Код ошибки.
    int error_code = 0;

    // Профессии.
    job_t jobs[MAX_JOBS_NUMBER];

    // Количество профессий.
    int jobs_number = -1;

    // Ширина каждой колонки.
    int cols_width[COLUMNS_NUMBER] = {0};

    // Входной файл.
    FILE *f_in = NULL;
    // Выходной файл.
    FILE *f_out = NULL;

    // Проверяем соответствие количества аргументов ожидаемому.
    if (argc != 3)
    {
        puts("ERROR! INCORRECT NUMBER OF PARAMETERS.");
        error_code = 1;
        goto ProgramExitPoint;
    }

    // Открываем файлы.
    f_in = fopen(argv[1], "r");
    f_out = fopen(argv[2], "w");
    if (!f_in || !f_out)
    {
        puts("ERROR! FILE NOT FOUND.");
        error_code = 1;
        goto ProgramExitPoint;
    }

    // Читаем профессии из файла.
    if (!read_jobs(f_in, cols_width, &jobs_number, jobs))
    {
        error_code = 1;
    }

    // Печатаем форматированную таблицу с профессиями.
    print_jobs(f_out, cols_width, jobs_number, jobs);

    ProgramExitPoint:
    // Закрываем открытые файлы.
    if (f_in)
    {
        fclose(f_in);
    }
    if (f_out)
    {
        fclose(f_out);
    }

    return error_code;
}
