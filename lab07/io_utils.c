#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "declarations.h"
#include "io_utils.h"
#include "token_utils.h"

// Процедура добавления очередного символа к текущему токену.
int add_symbol(char *token, char c, int *index);

int parse_punctuators(char *str, Token **tokens_array, int *length, int line,
                      int column, int *n, int *array_size);

// Функция считывания токенов из файла.
int read_tokens(FILE *f, Token **tokens_array, int *n)
{
    assert(f);

    int array_size = 0;

    // Текущий токен.
    char cur_token[MAX_TOKEN_LENGTH] = "";
    // Номер текущего символа в текущем токене.
    int cur_token_pos = 0;
    // Текущая строка.
    int line = 0;
    // Позиция в текущей строке.
    int column = -1;

    // Статус.
    State state = initial;

    // Текущий символ.
    char c;

    // Считываем все символы из файла.
    while (fscanf(f, "%c", &c) == 1)
    {
        column++;
        SelectionStart:
        switch (state)
        {
            case initial:
                // Директива компилятора.
                if (c == '#')
                {
                    state = compiler_directive;
                    continue;
                }
                // Строковый литерал.
                if (c == '\"')
                {
                    add_symbol(cur_token, c, &cur_token_pos);
                    state = string;
                    continue;
                }
                // Символьный литерал.
                if (c == '\'')
                {
                    add_symbol(cur_token, c, &cur_token_pos);
                    state = char_literal;
                    continue;
                }
                // Комментарий.
                if (c == '/')
                {
                    if (fscanf(f, "%c", &c) != 1)
                    {
                        puts("ERROR");
                        return -1;
                    }
                    column++;
                    // Однострочный комментарий.
                    if (c == '/')
                    {
                        state = single_line_comment;
                        continue;
                    }
                    // Многострочный комментарий.
                    else if (c == '*')
                    {
                        state = multiline_comment;
                        continue;
                    }
                    // Пунктуатор.
                    else
                    {
                        state = punctuators;
                        goto SelectionStart;
                    }
                }
                // Переход на новую строку.
                if ((c == '\0') || (c == '\n'))
                {
                    line++;
                }
                // Переменная.
                if (contains(c, letters, LETTERS_NUM))
                {
                    add_symbol(cur_token, c, &cur_token_pos);
                    state = variable;
                }
                // Цифра.
                if (contains(c, digits, DIGITS_NUM))
                {
                    add_symbol(cur_token, c, &cur_token_pos);
                    state = digit_constant;
                }
                // Пунктуатор.
                if (contains(c, signs, SIGNS_NUM))
                {
                    add_symbol(cur_token, c, &cur_token_pos);
                    state = punctuators;
                }
                break;

            case variable:
                // Переменные содержат только буквы и цифры.
                if (contains(c, letters, LETTERS_NUM) ||
                    contains(c, digits, DIGITS_NUM))
                {
                    add_symbol(cur_token, c, &cur_token_pos);
                }
                // Если найден другой символ, значит уже не переменная.
                else
                {
                    add_token(cur_token, tokens_array, &cur_token_pos, line, column,
                              n, &array_size, identifier);
                    state = initial;
                    goto SelectionStart;
                }
                break;

            case digit_constant:
                if ((c == '.') || (c == 'e') || (c == 'E') || (c == 'x') || (c == 'X'))
                {
                    add_symbol(cur_token, c, &cur_token_pos);
                }
                else if (contains(c, digits, DIGITS_NUM))
                {
                    add_symbol(cur_token, c, &cur_token_pos);
                }
                else
                {
                    add_token(cur_token, tokens_array, &cur_token_pos, line, column,
                              n, &array_size, constant);
                    state = initial;
                    goto SelectionStart;
                }
                break;

            case punctuators:
                if (contains(c, signs, SIGNS_NUM))
                {
                    add_symbol(cur_token, c, &cur_token_pos);
                }
                else
                {
                    parse_punctuators(cur_token, tokens_array, &cur_token_pos,
                                      line, column, n, &array_size);
                    state = initial;
                    goto SelectionStart;
                }
                break;

            case single_line_comment:
                if ((c == '\0') || (c == '\n'))
                {
                    line++;
                    state = initial;
                }
                break;

            case multiline_comment:
                if ((c == '\0') || (c == '\n'))
                {
                    line++;
                }
                if (c == '*')
                {
                    // Читаем из файла следующий символ.
                    if (fscanf(f, "%c", &c) != 1)
                    {
                        puts("ERROR");
                        return -1;
                    }
                    column++;
                    if (c == '/')
                    {
                        state = initial;
                    }
                    else
                    {
                        goto SelectionStart;
                    }
                }
                break;

            case compiler_directive:
                if ((c == '\0') || (c == '\n'))
                {
                    line++;
                    state = initial;
                }
                break;

            case string:
                if ((c == '\0') || (c == '\n'))
                {
                    line++;
                }
                else if (c == '\"')
                {
                    add_symbol(cur_token, c, &cur_token_pos);
                    add_token(cur_token, tokens_array, &cur_token_pos, line, column,
                              n, &array_size, string_literal);
                    state = initial;
                }
                else
                {
                    add_symbol(cur_token, c, &cur_token_pos);
                }
                break;

            case char_literal:
                add_symbol(cur_token, c, &cur_token_pos);
                if (c == '\'')
                {
                    add_token(cur_token, tokens_array, &cur_token_pos, line, column,
                              n, &array_size, string_literal);
                    state = initial;
                }
                break;
        }
    }

    return 0;
}

int parse_punctuators(char *str, Token **tokens_array, int *length, int line,
                      int column, int *n, int *array_size)
{
    int p = -1;
    char c;
    char token[MAX_TOKEN_LENGTH] = "";
    int token_pos = 0;
    while (p < (*length))
    {
        p++;
        c = str[p];
        AnalysisStart:
        switch (c)
        {
            case '~':
                add_symbol(token, c, &token_pos);
                add_token(token, tokens_array, &token_pos, line, column + p,
                          n, array_size, punctuator);
                break;

            case '[':
                add_symbol(token, c, &token_pos);
                add_token(token, tokens_array, &token_pos, line, column + p,
                          n, array_size, punctuator);
                break;

            case ']':
                add_symbol(token, c, &token_pos);
                add_token(token, tokens_array, &token_pos, line, column + p,
                          n, array_size, punctuator);
                break;

            case '(':
                add_symbol(token, c, &token_pos);
                add_token(token, tokens_array, &token_pos, line, column + p,
                          n, array_size, punctuator);
                break;

            case ')':
                add_symbol(token, c, &token_pos);
                add_token(token, tokens_array, &token_pos, line, column + p,
                          n, array_size, punctuator);
                break;

            case '{':
                add_symbol(token, c, &token_pos);
                add_token(token, tokens_array, &token_pos, line, column + p,
                          n, array_size, punctuator);
                break;

            case '}':
                add_symbol(token, c, &token_pos);
                add_token(token, tokens_array, &token_pos, line, column + p,
                          n, array_size, punctuator);
                break;

            case ':':
                add_symbol(token, c, &token_pos);
                add_token(token, tokens_array, &token_pos, line, column + p,
                          n, array_size, punctuator);
                break;

            case ';':
                add_symbol(token, c, &token_pos);
                add_token(token, tokens_array, &token_pos, line, column + p,
                          n, array_size, punctuator);
                break;

            case ',':
                add_symbol(token, c, &token_pos);
                add_token(token, tokens_array, &token_pos, line, column + p,
                          n, array_size, punctuator);
                break;

            case '?':
                add_symbol(token, c, &token_pos);
                add_token(token, tokens_array, &token_pos, line, column + p,
                          n, array_size, punctuator);
                break;

            case '+':
                add_symbol(token, c, &token_pos);
                p++;
                c = str[p];
                if ((c == '+') || (c == '='))
                {
                    add_symbol(token, c, &token_pos);
                    add_token(token, tokens_array, &token_pos, line, column + p,
                              n, array_size, punctuator);
                }
                else if (c == '\0')
                {
                    add_token(token, tokens_array, &token_pos, line, column + p,
                              n, array_size, punctuator);
                    break;
                }
                else
                {
                    add_token(token, tokens_array, &token_pos, line, column + p - 1,
                              n, array_size, punctuator);
                    goto AnalysisStart;
                }
                break;

            case '-':
                add_symbol(token, c, &token_pos);
                p++;
                c = str[p];
                if ((c == '-') || (c == '=') || (c == '>'))
                {
                    add_symbol(token, c, &token_pos);
                    add_token(token, tokens_array, &token_pos, line, column + p,
                              n, array_size, punctuator);
                }
                else if (c == '\0')
                {
                    add_token(token, tokens_array, &token_pos, line, column + p,
                              n, array_size, punctuator);
                    break;
                }
                else
                {
                    add_token(token, tokens_array, &token_pos, line, column + p - 1,
                              n, array_size, punctuator);
                    goto AnalysisStart;
                }
                break;

            case '&':
                add_symbol(token, c, &token_pos);
                p++;
                c = str[p];
                if ((c == '&') || (c == '='))
                {
                    add_symbol(token, c, &token_pos);
                    add_token(token, tokens_array, &token_pos, line, column + p,
                              n, array_size, punctuator);
                }
                else if (c == '\0')
                {
                    add_token(token, tokens_array, &token_pos, line, column + p,
                              n, array_size, punctuator);
                    break;
                }
                else
                {
                    add_token(token, tokens_array, &token_pos, line, column + p - 1,
                              n, array_size, punctuator);
                    goto AnalysisStart;
                }
                break;

            case '*':
                add_symbol(token, c, &token_pos);
                p++;
                c = str[p];
                if (c == '=')
                {
                    add_symbol(token, c, &token_pos);
                    add_token(token, tokens_array, &token_pos, line, column + p,
                              n, array_size, punctuator);
                }
                else if (c == '\0')
                {
                    add_token(token, tokens_array, &token_pos, line, column + p - 1,
                              n, array_size, punctuator);
                    break;
                }
                else
                {
                    add_token(token, tokens_array, &token_pos, line, column + p - 1,
                              n, array_size, punctuator);
                    goto AnalysisStart;
                }
                break;

            case '!':
                add_symbol(token, c, &token_pos);
                p++;
                c = str[p];
                if (c == '=')
                {
                    add_symbol(token, c, &token_pos);
                    add_token(token, tokens_array, &token_pos, line, column + p,
                              n, array_size, punctuator);
                }
                else if (c == '\0')
                {
                    add_token(token, tokens_array, &token_pos, line, column + p - 1,
                              n, array_size, punctuator);
                    break;
                }
                else
                {
                    add_token(token, tokens_array, &token_pos, line, column + p - 1,
                              n, array_size, punctuator);
                    goto AnalysisStart;
                }
                break;

            case '/':
                add_symbol(token, c, &token_pos);
                p++;
                c = str[p];
                if (c == '/')
                {
                    add_symbol(token, c, &token_pos);
                    add_token(token, tokens_array, &token_pos, line, column + p,
                              n, array_size, punctuator);
                }
                else if (c == '\0')
                {
                    add_token(token, tokens_array, &token_pos, line, column + p - 1,
                              n, array_size, punctuator);
                    break;
                }
                else
                {
                    add_token(token, tokens_array, &token_pos, line, column + p - 1,
                              n, array_size, punctuator);
                    goto AnalysisStart;
                }
                break;

            case '^':
                add_symbol(token, c, &token_pos);
                p++;
                c = str[p];
                if (c == '=')
                {
                    add_symbol(token, c, &token_pos);
                    add_token(token, tokens_array, &token_pos, line, column + p,
                              n, array_size, punctuator);
                }
                else if (c == '\0')
                {
                    add_token(token, tokens_array, &token_pos, line, column + p - 1,
                              n, array_size, punctuator);
                    break;
                }
                else
                {
                    add_token(token, tokens_array, &token_pos, line, column + p - 1,
                              n, array_size, punctuator);
                    goto AnalysisStart;
                }
                break;

            case '%':
                add_symbol(token, c, &token_pos);
                p++;
                c = str[p];
                if (c == '=')
                {
                    add_symbol(token, c, &token_pos);
                    add_token(token, tokens_array, &token_pos, line, column + p,
                              n, array_size, punctuator);
                }
                else if (c == '\0')
                {
                    add_token(token, tokens_array, &token_pos, line, column + p - 1,
                              n, array_size, punctuator);
                    break;
                }
                else
                {
                    add_token(token, tokens_array, &token_pos, line, column + p - 1,
                              n, array_size, punctuator);
                    goto AnalysisStart;
                }
                break;

            case '=':
                add_symbol(token, c, &token_pos);
                p++;
                c = str[p];
                if (c == '=')
                {
                    add_symbol(token, c, &token_pos);
                    add_token(token, tokens_array, &token_pos, line, column + p,
                              n, array_size, punctuator);
                }
                else if (c == '\0')
                {
                    add_token(token, tokens_array, &token_pos, line, column + p - 1,
                              n, array_size, punctuator);
                    break;
                }
                else
                {
                    add_token(token, tokens_array, &token_pos, line, column + p - 1,
                              n, array_size, punctuator);
                    goto AnalysisStart;
                }
                break;

            case '|':
                add_symbol(token, c, &token_pos);
                p++;
                c = str[p];
                if ((c == '|') || (c == '='))
                {
                    add_symbol(token, c, &token_pos);
                    add_token(token, tokens_array, &token_pos, line, column + p,
                              n, array_size, punctuator);
                }
                else if (c == '\0')
                {
                    add_token(token, tokens_array, &token_pos, line, column + p - 1,
                              n, array_size, punctuator);
                    break;
                }
                else
                {
                    add_token(token, tokens_array, &token_pos, line, column + p - 1,
                              n, array_size, punctuator);
                    goto AnalysisStart;
                }
                break;
        }
        break;
    }

    str[0] = '\0';
    *length = 0;
    return 0;
}

// Процедура добавления очередного символа к текущему токену.
int add_symbol(char *token, char c, int *index)
{
    assert(*index < MAX_TOKEN_LENGTH);
    token[*index] = c;
    token[*index + 1] = '\0';
    (*index)++;
    return 0;
}

int print_tokens(FILE *f, Token *tokens_array, int n)
{
    assert(f);
    fprintf(f, "<Table_of_tokens>\n");
    for (int i = 0; i < n; i++)
    {
        fprintf(f, "\t<Token>\n");
        fprintf(f, "\t\t<Category_of_token>");
        switch (tokens_array[i].category)
        {
            case keyword:
                fprintf(f, "%s", "keyword");
                break;

            case identifier:
                fprintf(f, "%s", "identifier");
                break;

            case constant:
                fprintf(f, "%s", "constant");
                break;

            case string_literal:
                fprintf(f, "%s", "string_literal");
                break;

            case punctuator:
                fprintf(f, "%s", "punctuator");
                break;
        }
        fprintf(f, "</Category_of_token>\n");
        fprintf(f, "\t\t<Name_of_token>%s</Name_of_token>\n", tokens_array[i].token_name);
        fprintf(f, "\t\t<Number_of_line>%d</Number_of_line>\n", tokens_array[i].line);
        fprintf(f, "\t\t<Position_in_line>%d</Position_in_line>\n", tokens_array[i].column);
        fprintf(f, "\t\t<Name_length>%d</Name_length>\n", tokens_array[i].token_name_length);
        fprintf(f, "\t</Token>\n");
    }

    fprintf(f, "</Table_of_tokens>\n");

    return 0;
}
