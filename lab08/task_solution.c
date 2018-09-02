#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "declarations.h"
#include "stack_utils.h"
#include "queue_utils.h"
#include "task_solution.h"

#define FUNCTIONS_NUM 10           // Количество функций.
#define MAX_FUNCTION_NAME_LENGTH 4 // Максимальная длина имени функции.

// Массив имен функций.
char functions[FUNCTIONS_NUM][MAX_FUNCTION_NAME_LENGTH] =
{
    "abs", "asin", "acos", "atg", "cos", "exp", "sin", "ln", "sqrt", "tg"
};


// Добавляет символ к строке.
int add_symbol(char, char **);
// Определяет, является ли строка именем функции.
int is_function(const char *);
// Определяет приоритет операции.
int priority(const char *);
// Определяет, является ли функция лево-ассоциативной.
int left_associative(const char *);

int get_tokens(char *, token_struct_t **, int *);

int get_reversed(token_struct_t *tokens_array, int n, queue_node_t **queue_head,
                  queue_node_t **queue_tail);


int set_tokens_array_length(token_struct_t **tokens_array, int n)
{
    token_struct_t *v = (token_struct_t*)realloc(*tokens_array,
                                                 n * sizeof(token_struct_t));
    if (!v)
    {
        return 0;
    }

    *tokens_array = v;
    return 1;
}

int add_token(char *str, token_t type, token_struct_t **tokens_array, int *n)
{
    (*n)++;
    if (!set_tokens_array_length(tokens_array, *n))
    {
        return 0;
    }
    (*tokens_array)[*n - 1].name = str;
    (*tokens_array)[*n - 1].type = type;

    return 1;
}


int priority(const char* opr)
{
    if (is_function(opr))
    {
        return 5;
    }
    if (strcmp(opr, "^") == 0)
    {
        return 4;
    }
    if (strcmp(opr, "\\") == 0)
    {
        return 3;
    }
    if ((strcmp(opr, "*") == 0) || (strcmp(opr, "/") == 0) || (strcmp(opr, "%") == 0))
    {
        return 2;
    }
    if ((strcmp(opr, "-") == 0) || (strcmp(opr, "+") == 0))
    {
        return 1;
    }
    return 0;
}


int left_associative(const char *opr)
{
    if (is_function(opr))
    {
        return 1;
    }
    if (strcmp(opr, "^") == 0)
    {
        return 1;
    }
    if (strcmp(opr, "\\") == 0)
    {
        return 0;
    }
    if ((strcmp(opr, "*") == 0) || (strcmp(opr, "/") == 0) || (strcmp(opr, "%") == 0))
    {
        return 1;
    }
    if ((strcmp(opr, "-") == 0) || (strcmp(opr, "+") == 0))
    {
        return 1;
    }
    return 1;
}

int is_function(const char *str)
{
    for (int i = 0; i < FUNCTIONS_NUM; i++)
    {
        if (strlen(str) != strlen(functions[i]))
        {
            continue;
        }
        if (strcmp(str, functions[i]))
        {
            return 1;
        }
    }
    return 0;
}


int infix_to_reversed(char *expression, queue_node_t **queue_head,
                      queue_node_t **queue_tail)
{
    token_struct_t *tokens_array = NULL;
    int n = 0;
    if (!get_tokens(expression, &tokens_array, &n))
    {
        return 0;
    }
    if (!get_reversed(tokens_array, n, queue_head, queue_tail))
    {
        return 0;
    }
    return 1;
}


int get_tokens(char *expression, token_struct_t **tokens_array, int *n)
{
    typedef enum
    {
        st_initial,
        st_variable,
        st_constant
    } states_t;

    char *str = NULL;
    char c;

    int expression_length = strlen(expression);
    states_t state = st_initial;
    for (int i = 0; i < expression_length; i++)
    {
        c = expression[i];
        switch (state)
        {
            case st_initial:
                if (isalpha(c))
                {
                    if (!add_symbol(c, &str))
                    {
                        return 0;
                    }
                    state = st_variable;
                    continue;
                }
                if (isdigit(c))
                {
                    if (!add_symbol(c, &str))
                    {
                        return 0;
                    }
                    state = st_constant;
                    continue;
                }
                if (ispunct(c))
                {
                    if (!add_symbol(c, &str))
                    {
                        return 0;
                    }
                    if (!add_token(str, operation, tokens_array, n))
                    {
                        return 0;
                    }
                    str = NULL;
                    continue;
                }
                return 0;

            case st_variable:
                if (isalpha(c))
                {
                    if (!add_symbol(c, &str))
                    {
                        return 0;
                    }
                    continue;
                }
                if (isdigit(c))
                {
                    free(str);
                    free(*tokens_array);
                    return 0;
                }
                if (ispunct(c))
                {
                    if (is_function(str))
                    {
                        if (!add_token(str, function, tokens_array, n))
                        {
                            return 0;
                        }
                    }
                    else
                    {
                        if (!add_token(str, variable, tokens_array, n))
                        {
                            return 0;
                        }
                    }
                    str = NULL;
                    if (!add_symbol(c, &str))
                    {
                        return 0;
                    }
                    if (!add_token(str, operation, tokens_array, n))
                    {
                        return 0;
                    }
                    str = NULL;
                    state = st_initial;
                    continue;
                }
                return 0;

            case st_constant:
                if (isalpha(c))
                {
                    free(str);
                    free(*tokens_array);
                    return 0;
                }
                if (isdigit(c))
                {
                    if (!add_symbol(c, &str))
                    {
                        return 0;
                    }
                    continue;
                }
                if (ispunct(c))
                {
                    if (!add_token(str, constant, tokens_array, n))
                    {
                        return 0;
                    }
                    str = NULL;
                    if (!add_symbol(c, &str))
                    {
                        return 0;
                    }
                    if (!add_token(str, operation, tokens_array, n))
                    {
                        return 0;
                    }
                    str = NULL;
                    state = st_initial;
                    continue;
                }
                return 0;
        }
    }
    if (str)
    {
        if (isalpha(c))
        {
            if (is_function(str))
            {
                if (!add_token(str, function, tokens_array, n))
                {
                    return 0;
                }
            }
            else
            {
                if (!add_token(str, variable, tokens_array, n))
                {
                    return 0;
                }
            }
        }
        else
        {
            if (!add_token(str, constant, tokens_array, n))
            {
                return 0;
            }
        }
        str = NULL;
    }

    return 1;
}


int get_reversed(token_struct_t *tokens_array, int n, queue_node_t **queue_head,
                  queue_node_t **queue_tail)
{
    stack_node_t *stack_top = NULL;
    for (int i = 0; i < n; i++)
    {
        if ((tokens_array[i].type == constant) || (tokens_array[i].type == variable))
        {
            if (!enqueue(queue_head, queue_tail, tokens_array[i]))
            {
                return 0;
            }
        }
        else if (tokens_array[i].type == function)
        {
            tokens_array[i].type = operation;
            if (!push(&stack_top, tokens_array[i]))
            {
                return 0;
            }
        }
        else if (strncmp(tokens_array[i].name, "(", 1) == 0)
        {
            if (!push(&stack_top, tokens_array[i]))
            {
                return 0;
            }
        }
        else if (strncmp(tokens_array[i].name, ")", 1) == 0)
        {
            while (!stack_is_empty(stack_top))
            {
                if (strncmp(stack_peek(stack_top).name, "(", 1) != 0)
                {
                    if (!enqueue(queue_head, queue_tail, pop(&stack_top)))
                    {
                        return 0;
                    }
                }
                else
                {
                    token_struct_t token = pop(&stack_top);
                    free(token.name);
                    break;
                }
            }
        }
        else if (tokens_array[i].type == operation)
        {
            if (strncmp(tokens_array[i].name, "-", 1) == 0)
            {
                if ((i == 0) || (tokens_array[i - 1].type == operation))
                {
                    free(tokens_array[i].name);
                    tokens_array[i].name = NULL;
                    add_symbol('\\', &tokens_array[i].name);
                }
            }

            int cur_priority = priority(tokens_array[i].name);

            token_struct_t token;
            if (left_associative(tokens_array[i].name))
            {
                while (!stack_is_empty(stack_top))
                {
                    token = stack_peek(stack_top);
                    if (cur_priority <= priority(token.name))
                    {
                        token = pop(&stack_top);
                        if (!enqueue(queue_head, queue_tail, token))
                        {
                            return 0;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                while (!stack_is_empty(stack_top))
                {
                    token = stack_peek(stack_top);
                    if (cur_priority < priority(token.name))
                    {
                        token = pop(&stack_top);
                        if (!enqueue(queue_head, queue_tail, token))
                        {
                            return 0;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
            if (!push(&stack_top, tokens_array[i]))
            {
                return 0;
            }
        }
    }
    while (!stack_is_empty(stack_top))
    {
        if (!enqueue(queue_head, queue_tail, pop(&stack_top)))
        {
            return 0;
        }
    }
    return 1;
}


int add_symbol(char c, char **str)
{
    int init_length = 0;
    if (*str)
    {
        init_length = strlen(*str);
    }

    char *temp;
    if (!init_length)
    {
        temp = (char*)malloc(2 * sizeof(char));
        if (!temp)
        {
            return 0;
        }
        temp[0] = c;
        temp[1] = '\0';
    }
    else
    {
        temp = realloc(*str, (init_length + 2) * sizeof(char));
        if (!temp)
        {
            return 0;
        }
        temp[init_length] = c;
        temp[init_length + 1] = '\0';
    }

    *str = temp;
    return 1;
}

typedef double(*math_f_t)(double x);

math_f_t get_function(const char *str)
{
    //"abs", "asin", "acos", "atg", "cos", "exp", "sin", "ln", "sqrt", "tg"
    if (strcmp(str, "abs") == 0)
    {
        return fabs;
    }
    if (strcmp(str, "asin") == 0)
    {
        return asin;
    }
    if (strcmp(str, "acos") == 0)
    {
        return acos;
    }
    if (strcmp(str, "atg") == 0)
    {
        return acos;
    }
    if (strcmp(str, "cos") == 0)
    {
        return cos;
    }
    if (strcmp(str, "exp") == 0)
    {
        return acos;
    }
    if (strcmp(str, "sin") == 0)
    {
        return sin;
    }
    if (strcmp(str, "ln") == 0)
    {
        return log;
    }
    if (strcmp(str, "sqrt") == 0)
    {
        return sqrt;
    }
    if (strcmp(str, "tg") == 0)
    {
        return tan;
    }
    return NULL;
}


int count_result(queue_node_t *queue_head, double *result)
{
    stack_node_t *stack_top = NULL;
    queue_node_t *queue_pointer = queue_head;

    while (queue_pointer)
    {
        if ((queue_pointer->token.type == variable) ||
            (queue_pointer->token.type == constant))
        {
            push(&stack_top, queue_pointer->token);
        }
        else
        {
            token_struct_t v1, v2, v;
            v.type = constant;
            if (is_function(queue_pointer->token.name))
            {
                v1 = pop(&stack_top);
                v.value = get_function(queue_pointer->token.name)(v1.value);
            }
            else if (strncmp(queue_pointer->token.name, "\\", 1) == 0)
            {
                v1 = pop(&stack_top);
                v.value = -v1.value;
            }
            else
            {
                v2 = pop(&stack_top);
                v1 = pop(&stack_top);
                if (strncmp(queue_pointer->token.name, "*", 1) == 0)
                {
                    v.value = v1.value * v2.value;
                }
                else if (strncmp(queue_pointer->token.name, "/", 1) == 0)
                {
                    v.value = v1.value / v2.value;
                }
                else if (strncmp(queue_pointer->token.name, "+", 1) == 0)
                {
                    v.value = v1.value + v2.value;
                }
                else if (strncmp(queue_pointer->token.name, "-", 1) == 0)
                {
                    v.value = v1.value - v2.value;
                }
                else if (strncmp(queue_pointer->token.name, "^", 1) == 0)
                {
                    v.value = pow(v1.value, v2.value);
                }
            }
            push(&stack_top, v);
        }
        queue_pointer = queue_pointer->next;
    }
    token_struct_t token = pop(&stack_top);
    *result = token.value;

    return 1;
}
