#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "declarations.h"
#include "integral_calculation.h"

void countIntegral(int a, int b, TReal eps, Function f, int maxIterations, int method)
{
    int n;
    if (method == 2)
    {
        n = floor((b - a) / 2 * sqrt(sqrt(eps))) + 1;
    }
    else
    {
        n = floor((b - a) / sqrt(eps)) + 1;
    }

    TReal s1; // Значение интеграла при первом числе участков.
    TReal s2; // Значение интеграла при втором числе участков.

    int iterations = 0;
    int error = 0;

    do
    {
        iterations++;
        if (iterations > maxIterations)
        {
            error = 1;
            break;
        }

        switch (method)
        {
            case 1:
                methodTrapezium(a, b, f, n, &s1);
                break;

            case 2:
                methodSimson(a, b, f, n, &s1);
                break;

            case 3:
                method38(a, b, f, n, &s1);
                break;
        }

        s2 = s1;
        n *= 2;

        switch (method)
        {
            case 1:
                methodTrapezium(a, b, f, n, &s1);
                break;

            case 2:
                methodSimson(a, b, f, n, &s1);
                break;

            case 3:
                method38(a, b, f, n, &s1);
                break;
        }
        n *= 2;
    }
    while(fabs(s2 - s1) > eps);
    if (error == 0)
    {
        n /= 2;
        printf("Number of segments: %d \n", n);
        printf("Integral value: %f \n", s1);
    }
    else
    {
        printf("Error: exactitude needed can not be reached.");
    }
}

void methodTrapezium(TReal a, TReal b, Function f, int n, TReal *s)
{
    assert(fabs(n) > 1e-15);

    TReal h = (b - a) / n;

    *s = 0;
    TReal x = a;
    if (n > 1)
    {
        for (int i = 1; i < n; i++)
        {
            x += h;
            *s += f(x);
        }
    }

    *s = h * (f(a) + f(b) + (*s + *s)) / 2;
}

void methodSimson(TReal a, TReal b, Function f, int n, TReal *s)
{
    assert(fabs(n) > 1e-15);

    TReal h = (b - a) / n;
    *s = 0;
    TReal x = a + h;
    while (x < b)
    {
        *s += 4 * f(x);
        x += h;
        *s += 2 * f(x);
        x += h;
    }
    *s = h / 3 * (*s + f(a) - f(b));
}

void method38(TReal a, TReal b, Function f, int n, TReal *s)
{
    assert(fabs(n) > 1e-15);

    TReal h = (b - a) / (3 * n);
    *s = f(a) + f(b);
    int m = (3 * n) - 1;
    TReal x = a;
    for (int i = 1; i <= m; i++)
    {
        x += h;
        if ((i % 3) == 0)
        {
            *s += 2 * f(x);
        }
        else
        {
            *s += 3 * f(x);
        }
    }
    *s *= 3 * h / 8;
}
