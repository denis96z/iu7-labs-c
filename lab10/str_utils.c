#include <stdio.h>
#include <assert.h>

#include "str_utils.h"

int str_copy(char *str1, char *str2, int index, int length)
{
    assert(str1);

    int end_pos = length - index;

    int j = 0;
    for (int i = index; i < end_pos; i++)
    {
        str2[j] = str1[i];
        j++;
    }
    str2[j] = '\0';

    return 1;
}
