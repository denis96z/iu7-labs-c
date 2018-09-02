/*!
    \file io_utils.h
    \brief Функции для обработки таблицы в файле.
*/

#ifndef IO_UTILS_H
#define IO_UTILS_H

/*!
    \fn read_jobs(FILE *f, int *cols_width, int *n, job_t *jobs)
    \brief Считывает профессии из файла.
    \param[in] f Имя файла.
    \param[out] cols_width Ширина столбцов.
    \param[out] n Количество профессий.
    \param[out] jobs Профессии.
    \return Успешность выполнения функции.
*/
int read_jobs(FILE *f, int *cols_width, int *n, job_t *jobs);

/*!
    \fn read_string(FILE *f, const int max_length, char *str, int *column_width)
    \brief Считывает строку из файла.
    \param[in] f Имя файла.
    \param[in] max_length Максимальная длина строки.
    \param[out] str Считанная строка.
    \param[out] column_width Ширина колонки.
    \return Успешность выполнения функции.
*/
int read_string(FILE *f, const int max_length, char *str, int *column_width);

/*!
    \fn read_int(FILE *f, int *value, int *column_width)
    \brief Считывает целое число из файла.
    \param[in] f Имя файла.
    \param[out] value Считанное число.
    \param[out] column_width Ширина колонки.
    \return Успешность выполнения функции.
*/
int read_int(FILE *f, int *value, int *column_width);

/*!
    \fn read_int(FILE *f, int *value, int *column_width)
    \brief Устанавливает ширину колонки.
    \param[in] new_width Имя файла.
    \param[out] column_width Изменяемая ширина колонки.
    \return Успешность выполнения функции.
*/
int set_column_width(int new_width, int *column_width);

/*!
    \fn print_jobs(FILE *f, int *cols_width, int n, job_t *jobs)
    \brief Печатает таблицу профессий в файл.
    \param[in] f Имя файла.
    \param[in] cols_width Ширина колонок.
    \param[in] n Количество профессий.
    \param[in] jobs Профессии.
    \return Успешность выполнения функции.
*/
int print_jobs(FILE *f, int *cols_width, int n, job_t *jobs);

/*!
    \fn print_table_head(FILE *f, int *cols_width)
    \brief Печатает заголовок таблицы в файл.
    \param[in] f Имя файла.
    \param[in] cols_width Ширина колонок.
*/
void print_table_head(FILE *f, int *cols_width);

#endif // IO_UTILS_H
