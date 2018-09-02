#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "declarations.h"
#include "string_utils.h"

#include "io_utils.h"

// Отладочная версия.
#define DEBUG

// Максимальная длина считываемой строки.
#define MAX_STRING_LENGTH 255
// Формат считывания строки.
#define STRING_SCANF_FORMAT "%255s"

int read_jobs(FILE *f, int *cols_width, int *n, job_t *jobs)
{
    // Считанная из файла строка.
    char temp[MAX_STRING_LENGTH];

#ifdef DEBUG
    assert(f);
    assert(*n == -1);
#endif

    // Читаем заголовок таблицы.
    for (int i = 0; i < COLUMNS_NUMBER; i++)
    {
        if (fscanf(f, STRING_SCANF_FORMAT, temp) != 1)
        {
            puts("ERROR! INCORRECT FILE STRUCTURE.");
            return 0;
        }
        cols_width[i] = strlen(temp);
    }

    // Читаем содержимое таблицы.
    while (!feof(f))
    {
        *n += 1;

        // Проверяем, достигнуто ли максимальное число профессий.
        if (*n == MAX_JOBS_NUMBER)
        {
            puts("JOBS LIMIT REACHED!");
            break;
        }

        // Считываем код профессии.
        if (!read_string(f, MAX_JOB_CODE_LENGTH, jobs[*n].job_code, &cols_width[0]))
        {
            return 1;
        }

        // Считываем оценку профессии.
        if (!read_int(f, &jobs[*n].job_grade, &cols_width[1]))
        {
            return 0;
        }

        // Считываем страну профессии.
        if (!read_string(f, MAX_JOB_COUNTRY_LENGTH, jobs[*n].job_country, &cols_width[2]))
        {
            return 0;
        }

        // Считываем название профессии.
        if (!read_string(f, MAX_JOB_TITLE_LENGTH, jobs[*n].job_title, &cols_width[3]))
        {
            return 0;
        }

        // Считываем минимальную заработную плату.
        if (!read_int(f, &jobs[*n].min_salary, &cols_width[4]))
        {
            return 0;
        }

        // Считываем максимальную заработную плату.
        if (!read_int(f, &jobs[*n].max_salary, &cols_width[5]))
        {
            return 0;
        }
    }

    return 1;
}

int read_string(FILE *f, const int max_length, char *str, int *column_width)
{
    // Считываемая строка.
    static char temp[MAX_STRING_LENGTH];
    // Длина считанной строки.
    int length = 0;

    // Читаем из файла строку.
    if (fscanf(f, STRING_SCANF_FORMAT, temp) != 1)
    {
        puts("ERROR! INCORRECT FILE STRUCTURE.");
        return 0;
    }

    // Проверяем строку на допустимость по длине.
    length = strlen(temp);
    if (length > max_length)
    {
        puts("ERROR! INCORRECT FILE STRUCTURE.");
        return 0;
    }

    // Изменяем ширину колонки в зависимости от длины строки.
    if (!set_column_width(length, column_width))
    {
        return 0;
    }

    // Записываем строку в таблицу.
    if (!copy_str(temp, 0, length, str))
    {
        puts("ERROR! INCORRECT FILE STRUCTURE.");
        return 0;
    }

    return 1;
}

int read_int(FILE *f, int *value, int *column_width)
{
    // Считываемая строка.
    static char temp[MAX_STRING_LENGTH];
    // Длина считанной строки.
    int length = 0;

    // Читаем из файла строку.
    if (fscanf(f, STRING_SCANF_FORMAT, temp) != 1)
    {
        puts("ERROR! INCORRECT FILE STRUCTURE.");
        return 0;
    }

    length = strlen(temp);

    // Изменяем ширину колонки в зависимости от длины строки.
    if (!set_column_width(length, column_width))
    {
        return 0;
    }

    // Проверяем строку на наличие посторонних символов (не цифр).
    if (!is_int(temp))
    {
        puts("ERROR! INCORRECT FILE STRUCTURE.");
        return 0;
    }

    *value = atoi(temp);

    return 1;
}

int set_column_width(int new_width, int *column_width)
{
    if (*column_width < new_width)
    {
        *column_width = new_width;
    }
    return 1;
}

int print_jobs(FILE *f, int *cols_width, int n, job_t *jobs)
{
    // Печатаем шапку таблицы.
    print_table_head(f, cols_width);

    // Печатаем таблицу.
    for (int i = 0; i < n; i++)
    {
        fprintf(f, "| ");
        fprintf(f, "%-*s", cols_width[0], jobs[i].job_code);
        fprintf(f, " | ");
        fprintf(f, "%*d", cols_width[1], jobs[i].job_grade);
        fprintf(f, " | ");
        fprintf(f, "%-*s", cols_width[2], jobs[i].job_country);
        fprintf(f, " | ");
        fprintf(f, "%-*s", cols_width[3], jobs[i].job_title);
        fprintf(f, " | ");
        fprintf(f, "%*d", cols_width[4], jobs[i].min_salary);
        fprintf(f, " | ");
        fprintf(f, "%*d", cols_width[5], jobs[i].max_salary);
        fprintf(f, " |\n");
    }
    // Печатаем нижнюю границу таблицы.
    fprintf(f, "+");
    for (int i = 0; i < COLUMNS_NUMBER; i++)
    {
        fprintf(f, "-");
        for (int j = 1; j <= cols_width[i]; j++)
        {
            fprintf(f, "-");
        }
        fprintf(f, "-+");
    }

    return 1;
}

void print_table_head(FILE *f, int *cols_width)
{
    fprintf(f, "+");
    for (int i = 0; i < COLUMNS_NUMBER; i++)
    {
        fprintf(f, "-");
        for (int j = 1; j <= cols_width[i]; j++)
        {
            fprintf(f, "-");
        }
        fprintf(f, "-+");
    }
    fprintf(f, "\n| ");
    fprintf(f, "%-*s", cols_width[0], "job_code");
    fprintf(f, " | ");
    fprintf(f, "%-*s", cols_width[1], "job_grade");
    fprintf(f, " | ");
    fprintf(f, "%-*s", cols_width[2], "job_country");
    fprintf(f, " | ");
    fprintf(f, "%-*s", cols_width[3], "job_title");
    fprintf(f, " | ");
    fprintf(f, "%-*s", cols_width[4], "min_salary");
    fprintf(f, " | ");
    fprintf(f, "%-*s", cols_width[5], "max_salary");
    fprintf(f, " |\n");
    fprintf(f, "+");
    for (int i = 0; i < COLUMNS_NUMBER; i++)
    {
        fprintf(f, "-");
        for (int j = 1; j <= cols_width[i]; j++)
        {
            fprintf(f, "-");
        }
        fprintf(f, "-+");
    }
    fprintf(f, "\n");
}
