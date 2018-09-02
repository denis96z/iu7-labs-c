#include <stdio.h>
#include <conio.h>
#include "declarations.h"
#include "io_unit.h"
#include "analysis_unit.h"

int main(void)
{
    int result = 0;

    char sourceFileName[MAX_PATH_LENGTH] = "digits.in";
    char digits[DIGITS_NUMBER][DIGIT_HEIGHT][DIGIT_WIDTH];

    if (readDataFromSource(sourceFileName, digits, DIGITS_NUMBER) == 0)
    {
        puts("Data loaded.");
    }
    else
    {
        puts("Error reading data file.");
        return 2;
    }

    char fileName[MAX_PATH_LENGTH];

    printf("%s", "Input file name: ");
    if (scanf("%s", fileName) != 1)
    {
        puts("Illegal file name.");
        return 3;
    }

    char time[DIGITS_IN_TIME][DIGIT_HEIGHT][DIGIT_WIDTH];
    int digitalTime[DIGITS_IN_TIME];

    result = readDataFromSource(fileName, time, DIGITS_IN_TIME);
    if (result == 0)
    {
        result = compareTime(digits, time, digitalTime);
    }

    if (result < 3)
    {
        if (printResultToFile("eclock.out.txt", digitalTime, result) == 0)
        {
            puts("Output file created.");
        }
        else
        {
            puts("Error creating output file.");
        }
    }
    else
    {
        puts("Error reading file.");
    }

    getch();
    return 0;
}
