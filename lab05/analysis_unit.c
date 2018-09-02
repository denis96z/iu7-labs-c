#include <stdio.h>
#include "declarations.h"

int compareTime(char digits[DIGITS_NUMBER][DIGIT_HEIGHT][DIGIT_WIDTH],
                char time[DIGITS_IN_TIME][DIGIT_HEIGHT][DIGIT_WIDTH], int digitalTime[DIGITS_IN_TIME])
{
    int matches, maxMatches;
    int counter;
    int maxIndex;
    for (int i = 0; i < DIGITS_IN_TIME; i++)
    {
        maxMatches = 0;
        counter = 1;
        for (int j = 0; j < DIGITS_NUMBER; j++)
        {
            matches = 0;
            for (int k = 0; k < DIGIT_HEIGHT; k++)
            {
                for (int m = 0; m < DIGIT_WIDTH; m++)
                {
                    if ((time[i][k][m] == '#') && (time[i][k][m] == digits[j][k][m]))
                    {
                        matches++;
                    }
                }
            }
            if (matches > maxMatches)
            {
                maxMatches = matches;
                maxIndex = j;
                counter = 1;
            }
            else
            {
                if (matches == maxMatches)
                {
                    counter++;
                }
            }
        }
        if (counter > 1)
        {
            return 1;
        }
        else
        {
            digitalTime[i] = maxIndex;
        }
    }

    return 0;
}
