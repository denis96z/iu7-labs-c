#include <stdio.h>
#include "declarations.h"

int readDataFromSource(char *fileName, char digits[][DIGIT_HEIGHT][DIGIT_WIDTH], int n)
{
    FILE *f = fopen(fileName, "r");
    if (!f)
    {
        return 1;
    }

    int i, j, k;
    char c;

    for (i = 0; i < DIGIT_HEIGHT; i++)
    {
        for (j = 0; j < n; j++)
        {
            do
            {
                if (fscanf(f, "%c", &c) != 1)
                {
                    fclose(f);
                    return 3;
                }
                if (c == '#')
                {
                    return 2;
                }
            }
            while (c != '.');

            for (k = 0; k < DIGIT_WIDTH; k++)
            {
                if (fscanf(f, "%c", &digits[j][i][k]) != 1)
                {
                    fclose(f);
                    return 3;
                }
            }
        }
    }

    fclose(f);
    return 0;
}

int printResultToFile(char *fileName, int digitalTime[DIGITS_IN_TIME], int result)
{
    FILE *f = fopen(fileName, "w");
    if (!f)
    {
        return 1;
    }

    switch (result)
    {
        case 0:
            fprintf(f, "%d%d:%d%d", digitalTime[0], digitalTime[1], digitalTime[2], digitalTime[3]);
            break;

        case 1:
            fprintf(f, "%s", "AMBIGUITY");
            break;

        case 2:
            fprintf(f, "%s", "ERROR");
            break;
    }

    fclose(f);
    return 0;
}
