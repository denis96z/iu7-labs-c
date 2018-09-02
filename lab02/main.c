#include <stdio.h>
#include <conio.h>

#include "declarations.h"
#include "functions.h"

#include "integral_calculation.h"
#include "roots_search.h"

int main(void)
{
    int functionOption = 0; // Выбранная функция.
    Function f;             // Исследуемая функция.
    Function df;            // Производная исследуемой функции.
    Function d2f;           // Вторая производная исследуемой функции.

    // Выбор функции.
    FunctionSelection:
    printf("Choose function: \n");
    printf("[1] Sin(x) \n");
    printf("[2] x^5 + 2x^4 - 16x^3 - 2x^2 + 15x \n");
    printf("[3] x - 2 \n");
    printf("> ");
    if (scanf("%d", &functionOption) != 1)
    {
        printf("Error: illegal symbol. Repeat input. \n");
        goto FunctionSelection;
    }
    switch (functionOption)
    {
        case 1:
            f = f1;
            df = df1;
            d2f = d2f1;
            break;

        case 2:
            f = f2;
            df = df2;
            d2f = d2f2;
            break;

        case 3:
            f = f3;
            df = df3;
            d2f = d2f3;
            break;

        default:
            printf("Error: item not found. Repeat input. \n");
            goto FunctionSelection;
    }

    int menuOption = 0; // Выбранный пункт меню.

    MenuItemSelection:
    printf("Choose an action: \n");
    printf("[1] Integral calculation. \n");
    printf("[2] Roots search. \n");
    printf("> ");

    if (scanf("%d", &menuOption) != 1)
    {
        printf("Error: illegal symbol. Repeat input. \n");
        goto MenuItemSelection;
    }
    if ((menuOption < 1) || (menuOption > 2))
    {
        printf("Error: item not found. Repeat input. \n");
        goto MenuItemSelection;
    }

    TReal lowerLimit, higherLimit; // Границы отрезка.

    LowerLimitInput:
    printf("Input the lower limit: ");
    if (scanf("%f", &lowerLimit) != 1)
    {
        printf("Error: illegal symbol. Repeat input. \n");
        goto LowerLimitInput;
    }

    HigherLimitInput:
    printf("Input the higher limit: ");
    if (scanf("%f", &higherLimit) != 1)
    {
        printf("Error: illegal symbol. Repeat input. \n");
        goto HigherLimitInput;
    }
    if (higherLimit < lowerLimit)
    {
        printf("Error: higher limit is less than lower limit. Repeat input. \n");
        goto HigherLimitInput;
    }

    TReal exactitude = 1e-3;      // Точность вычисления.
    int segmentsNumber = 100;     // Количество отрезков разбиения.
    int iterationsMaximum = 1000; // Максимальное число итераций.
    int method = 0;               // Метод.

    switch (menuOption)
    {
        case 1:
            IntegralCalculationMethodSelection:
            printf("Choose method: \n");
            printf("[1] Trapezium method. \n");
            printf("[2] Simson's method. \n");
            printf("[3] Newton's method. \n");
            printf("> ");
            // Проверка на ошибку ввода.
            if (scanf("%d", &method) != 1)
            {
                printf("Error: illegal symbol. Repeat input. \n");
                goto IntegralCalculationMethodSelection;
            }
            // Запускаем поиск в зависимости от выбранного метода.
            if ((method < 1) && (method > 3))
            {
                printf("Error: item not found. Repeat input. \n");
                goto IntegralCalculationMethodSelection;
            }
            countIntegral(lowerLimit, higherLimit, exactitude, f, iterationsMaximum, method);
            break;

        case 2:
            // Выбираем метод поиска корней.
            RootsSearchMethodSelection:
            printf("Choose method: \n");
            printf("[1] Bisection method. \n");
            printf("[2] Dichotomy method. \n");
            printf("[3] Newton's method. \n");
            printf("> ");
            if (scanf("%d", &method) != 1)
            {
                printf("Error: illegal symbol. Repeat input. \n");
                goto RootsSearchMethodSelection;
            }
            if ((method < 1) && (method > 3))
            {
                printf("Error: item not found. Repeat input. \n");
                goto RootsSearchMethodSelection;
            }
            searchRoots(lowerLimit, higherLimit, segmentsNumber, exactitude, iterationsMaximum, f, df, d2f, method);
            break;
    }

    getch();
}
