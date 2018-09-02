#include <stdio.h>
#include <conio.h>
#include <math.h>


int readNumbers(int *a, int *b)
{
    int result = 0;

    char fileName[255];
    printf("File name: ");
    scanf("%s", fileName);
    FILE *f = fopen(fileName, "r");
    if (!f)
    {
        result = 1;
        goto EndPoint;
    }

    if (fscanf(f, "%d", a) != 1)
    {
        result = 2;
        fclose(f);
        goto EndPoint;
    }
    if (fscanf(f, "%d", b) != 1)
    {
        result = 3;
        fclose(f);
        goto EndPoint;
    }

    EndPoint:
    return result;
}


int countDifferent(int a, int b)
{
    float values[10];

    values[0] = (float)(a + b);
    values[1] = (float)(a - b);
    values[2] = (float)(a * b);
    if (b != 0)
    {
        values[3] = (float)(a / b);
    }
    else
    {
        values[3] = NAN;
    }
    if ((a == 0) && (b <= 0))
    {
        values[4] = NAN;
    }
    else
    {
        values[4] = (float)(pow(a, b));
    }
    values[5] = (float)(b + a);
    values[6] = (float)(b - a);
    values[7] = (float)(b * a);
    if (a != 0)
    {
        values[8] = (float)(b / a);
    }
    else
    {
        values[8] = NAN;
    }
    if ((b == 0) && (a <= 0))
    {
        values[9] = NAN;
    }
    else
    {
        values[9] = (float)(pow(b, a));
    }

    int k = 0;
    int j;
    int flag;
    for (int i = 0; i < 10; i++)
    {
        if (isnan(values[i]))
        {
            continue;
        }
        j = i + 1;
        flag = 1;
        while ((j <= 10) && (flag == 1))
        {
            if (isnan(values[j]))
            {
                j++;
                continue;
            }
            if (values[j] == values[i])
            {
                flag = 0;
            }
            else
            {
                j++;
            }
        }
        if (flag == 1)
        {
            k++;
        }
    }

    return k;
}


void printResult(int result)
{
    FILE *f = fopen("out.txt", "w");
    if (f)
    {
        fprintf(f, "%d", result);
        fclose(f);
        printf("File 'out.txt' created.");
    }
    else
    {
        printf("Error creating file.");
    }
}


int main()
{
    int a, b;
    int result = 0;
    switch (readNumbers(&a, &b))
    {
        case 0:
            result = countDifferent(a, b);
            printResult(result);
            break;

        case 1:
            printf("File does not exist.");
            break;

        case 2:
            printf("Error reading number.");
            break;

        case 3:
            printf("Error reading number.");
            break;

    }
    getch();
}
