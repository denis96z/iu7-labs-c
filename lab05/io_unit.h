#ifndef IO_UNIT_H
#define IO_UNIT_H

int readDataFromSource(char *fileName, char digits[][DIGIT_HEIGHT][DIGIT_WIDTH], int n);

int printResultToFile(char *fileName, int digitalTime[DIGITS_IN_TIME], int result);

#endif // IO_UNIT_H
