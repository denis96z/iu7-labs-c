#include <math.h>
#include "declarations.h"
#include "functions.h"

TReal f1(TReal x)
{
    return sin(x);
}

TReal df1(TReal x)
{
    return cos(x);
}

TReal d2f1(TReal x)
{
    return (-sin(x));
}

TReal f2(TReal x)
{
    return ((pow(x, 5) + (2 * pow(x, 4)) - (16 * pow(x,3)) -
        (2 * pow(x, 2)) + (15 * x)));
}

TReal df2(TReal x)
{
    return (((5 * pow(x, 4)) + (8 * pow(x, 3)) - (48 * x * x) -
        (4 * x) + 15));
}

TReal d2f2(TReal x)
{
    return (((20 * pow(x, 3)) + (24 * x * x) - (96 * x) - 4));
}

TReal f3(TReal x)
{
    return (x - 2);
}

TReal df3(TReal x)
{
    return 1;
}

TReal d2f3(TReal x)
{
    return 0;
}
