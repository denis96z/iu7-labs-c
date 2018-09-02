/*!
    \file declarations.h
    \brief Объявления основных констант и типов.
*/

#ifndef DECLARATIONS_H
#define DECLARATIONS_H

/*!
    \def MAX_JOBS_NUMBER
    \brief Максимальное число профессий.
*/
#define MAX_JOBS_NUMBER 100

/*!
    \def COLUMNS_NUMBER
    \brief Количество столбцов таблицы.
*/
#define COLUMNS_NUMBER 6

/*!
    \def MAX_JOB_CODE_LENGTH
    \brief Максимальная длина строки кода профессии.
*/
#define MAX_JOB_CODE_LENGTH 10

/*!
    \def MAX_JOB_COUNTRY_LENGTH
    \brief Максимальная длина строки названия страны.
*/
#define MAX_JOB_COUNTRY_LENGTH 50

/*!
    \def MAX_JOB_TITLE_LENGTH
    \brief Максимальная длина строки названия профессии.
*/
#define MAX_JOB_TITLE_LENGTH 50

/*!
    \struct job_t
    \brief Описание профессии.
  */
typedef struct
{
    /*!
        \var job_code
        \brief Код профессии.
    */
    char job_code[MAX_JOB_CODE_LENGTH];

    /*!
        \var job_grade
        \brief Оценка профессии.
    */
    int job_grade;

    /*!
        \var job_country
        \brief Страна профессии.
    */
    char job_country[MAX_JOB_COUNTRY_LENGTH];

    /*!
        \var job_title
        \brief Название профессии.
    */
    char job_title[MAX_JOB_TITLE_LENGTH];

    /*!
        \var min_salary
        \brief Минимальная заработная плата.
    */
    int min_salary;

    /*!
        \var max_salary
        \brief Максимальная заработная плата.
    */
    int max_salary;
} job_t;

#endif // DECLARATIONS_H
