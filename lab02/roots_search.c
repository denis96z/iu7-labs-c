#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "declarations.h"
#include "roots_search.h"

void searchRoots(TReal a, TReal b, int n, TReal eps, int maxIterations,
    Function f, Function df, Function d2f, int method)
{
    TReal x; // Корень на отрезке.

    TReal h = (b - a) / n; // Шаг.

    TReal l = a;     // Левая граница отрезка.
    TReal r = a + h; // Правая граница отрезка.

    int counter = 0; // Счетчик корней.

    while (r <= b)
    {
        if ((f(l) * f(r)) < 0)
        {
            counter++;
            switch (method)
            {
                case 1:
                    switch (bisectionMethod(l, r, f, eps, maxIterations, &x))
                    {
                        case 0:
                            printf("Root %d: %7.4f \n", counter, x);
                            break;

                        case 1:
                            printf("Segment [%f, %f]: maximum iterations number exceeded. \n",
                                l, r);
                            break;
                    }
                    break;

                case 2:
                    if ((f(l) * d2f(l)) < 0)
                    {
                        TReal temp = l;
                        l = r;
                        r = temp;
                    }
                    switch (dichotomyMethod(l, r, f, eps, maxIterations, &x))
                    {
                        case 0:
                            printf("Root %d: %7.4f \n", counter, x);
                            break;

                        case 1:
                            printf("Segment [%f, %f]: maximum iterations number exceeded. \n",
                                l, r);
                            break;
                    }
                    break;

                case 3:
                    if ((f(l) * d2f(l)) > 0)
                    {
                        x = l;
                    }
                    else
                    {
                        x = r;
                    }
                    switch (newtonMethod(f, df, eps, maxIterations, &x))
                    {
                        case 0:
                            printf("Root %d: %7.4f \n", counter, x);
                            break;

                        case 1:
                            printf("Segment [%f, %f]: maximum iterations number exceeded. \n",
                                l, r);
                            break;
                    }
                    break;
            }
        }
        l = l + h;
        r = r + h;
    }
}

int bisectionMethod(TReal a, TReal b, Function f,
    float eps, int maxIterations, TReal *x)
{
    assert(b > a);

    int error = 0; // Код ошибки.

    int iterations = 0; // Количество итераций.

    TReal y1 = f(a);
    TReal y2;
    do
    {
        iterations++;
        // Проверка на превышение числа итераций.
        if (iterations > maxIterations)
        {
            error = 1;
            break;
        }

        *x = (a + b) / 2;
        y2 = f(*x);
        if ((y1 * y2) > 0)
        {
            a = *x;
        }
        else
        {
            b = *x;
        }
    }
    while (fabs(b - a) > eps);

    return error;
}

int dichotomyMethod(TReal a, TReal b, Function f,
    float eps, int maxIterations, TReal *x)
{
    assert(b > a);

    int error = 0; // Код ошибки.

    int iterations = 0; // Количество итераций.

    TReal y1 = f(b);
    TReal y2;

    TReal temp;
    do
    {
        iterations++;
        // Проверка на превышение числа итераций.
        if (iterations > maxIterations)
        {
            error = 1;
            break;
        }

        y2 = f(a);
        *x = a - (y2 * (a - b) / (y2 - y1));
        temp = fabs(a - *x);
        a = *x;
    }
    while (temp > eps);

    return error;
}

int newtonMethod(Function f, Function df,
    float eps, int maxIterations, TReal *x)
{
    int error = 0; // Код ошибки.

    int iterations = 0; // Число итераций.

    TReal xk;
    TReal dfdx;

    TReal temp;

    do
    {
        iterations++;
        // Проверка на превышение числа итераций.
        if (iterations > maxIterations)
        {
            error = 1;
            break;
        }

        dfdx = df(*x);
        // Проверка на нулевое значение производной.
        if (fabs(dfdx) < 1e-15)
        {
            error = 2;
            break;
        }

        xk = *x - (f(*x) / df(*x));
        temp = fabs(*x - xk);
        *x = xk;
    }
    while (temp > eps);

    return error;
}
