#include <stdio.h>
#include <string.h>

#define MAX_SENTENCES 100


int readData(char *fileName, char sentences[MAX_SENTENCES][255], int *n)
{
    FILE *f = fopen(fileName, "r");

    if (!f)
    {
        return 1;
    }

    char c;
    for (int i = 0; i < 3; i++)
    {
        if (fscanf(f, "%c", &c) != 1)
        {
            return 2;
        }
    }

    int counter = 0;
    int p = -1;
    while (!feof(f))
    {
        p++;
        fscanf(f, "%c", &c);

        sentences[counter][p] = c;
        if ((c == '.') || (c == '!') || (c == '?'))
        {
            sentences[counter][p + 1] = '\0';
            counter++;
            p = -1;
        }
    }

    *n = counter;

    return 0;
}


int seekLastExpressive(char sentences[MAX_SENTENCES][255], int n)
{
    int min = 1000;
    int minIndex = -1;
    for (int i = 0; i < n; i++)
    {
        int length = strlen(sentences[i]);
        if (sentences[i][length - 1] == '!')
        {
            if (length <= min)
            {
                min = length;
                minIndex = i;
            }
        }
    }
    return minIndex;
}


int printResult(char *fileName, char sentences[MAX_SENTENCES][255], int index)
{
    FILE *f = fopen(fileName, "w");

    if (!f)
    {
        return 1;
    }

    if (index > -1)
    {
        fputs(sentences[index], f);
    }
    else
    {
        fprintf(f, "%s", "NO");
    }

    fclose(f);
    return 0;
}


int main()
{
    char fileName[255];
    printf("Input file name: ");
    scanf("%s", fileName);

    char sentences[MAX_SENTENCES][255];
    int n = -1;

    readData(fileName, sentences, &n);

    int index = seekLastExpressive(sentences, n);

    char outFileName[255] = "out.txt";
    if (printResult(outFileName, sentences, index) == 0)
    {
        printf("File created.");
    }
    else
    {
        printf("Error!");
    }

    return 0;
}
