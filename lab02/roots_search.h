#ifndef ROOTS_SEARCH_H
#define ROOTS_SEARCH_H

void searchRoots(TReal a, TReal b, int n, TReal eps, int maxIterations,
    Function f, Function df, Function d2f, int method);
int bisectionMethod(TReal a, TReal b, Function f,
    float eps, int maxIterations, TReal *x);
int dichotomyMethod(TReal a, TReal b, Function f,
    float eps, int maxIterations, TReal *x);
int newtonMethod(Function f, Function df,
    float eps, int maxIterations, TReal *x);

#endif // ROOTS_SEARCH_H
