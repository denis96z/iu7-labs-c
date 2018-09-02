#include <stdio.h>
#include <math.h>

#define MAX_K 30


int readFromFile(int *k, int *m, int a[MAX_K], int *b, int x[MAX_K], int *n)
{
    int result = 0;

    char fileName[255];
    printf("File name: ");
    scanf("%s", fileName);
    FILE *f = fopen(fileName, "r");
    if (!f)
    {
        result = 1;
        fclose(f);
        goto EndPoint;
    }

    if (fscanf(f, "%d", k) != 1)
    {
        result = 1;
        fclose(f);
        goto EndPoint;
    }
    if (fscanf(f, "%d", m) != 1)
    {
        result = 1;
        fclose(f);
        goto EndPoint;
    }
    for (int i = 0; i < *k; i++)
    {
        if (fscanf(f, "%d", &a[i]) != 1)
        {
            result = 1;
            fclose(f);
            goto EndPoint;
        }
    }
    if (fscanf(f, "%d", b) != 1)
    {
        result = 1;
        fclose(f);
        goto EndPoint;
    }
    for (int i = 0; i < *k; i++)
    {
        if (fscanf(f, "%d", &x[i]) != 1)
        {
            result = 1;
            fclose(f);
            goto EndPoint;
        }
    }
    if (fscanf(f, "%d", n) != 1)
    {
        result = 1;
        fclose(f);
        goto EndPoint;
    }

    EndPoint:
    return result;
}


int countNumber(int k, int m, int a[MAX_K], int b, int x[MAX_K], int n)
{
    int xcurrent = 0;

    int extra[MAX_K];
    for (int i = 0; i < k; i++)
    {
        extra[i] = x[i];
    }

    for (int i = k + 1; i <= n; i++)
    {
        xcurrent = 0;
        for (int j = 0; j < k; j++)
        {
            xcurrent += a[j] * extra[k - j - 1];
        }
        xcurrent += b;
        xcurrent = xcurrent % m;
        for (int j = 0; j < (k - 1); j++)
        {
            extra[j] = extra[j + 1];
        }
        extra[k] = xcurrent;
    }

    return xcurrent;
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
    int k;
    int m;
    int a[MAX_K];
    int b;
    int x[MAX_K];
    int n;

    if (readFromFile(&k, &m, a, &b, x, &n) == 0)
    {
        int result = countNumber(k, m, a, b, x, n);
        printResult(result);
    }

    return 0;
}
