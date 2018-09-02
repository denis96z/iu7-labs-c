/*!
    \file string_utils.h
    \brief Функции для работы со строками.
*/

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

/*!
    \fn is_int(const char *str)
    \brief Проверяет, является ли входная строка целым числом.
    \param[in] str Входная строка.
    \return Признак, является ли строка числом.
*/
int is_int(const char *str);

/*!
    \fn copy_str(const char *str1, int index, int length, char *str2)
    \brief Копирует часть строки в новую строку.
    \param[in] str1 Входная строка.
    \param[in] index Индекс символа, с которого начинается копирование.
    \param[in] length Количество копируемых символов.
    \param[out] str2 Строка, в которую происходит копирование.
    \return Признак, является ли строка числом.
*/
int copy_str(const char *str1, int index, int length, char *str2);

#endif // STRING_UTILS_H
