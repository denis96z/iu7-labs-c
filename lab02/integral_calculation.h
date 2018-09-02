#ifndef INTEGRAL_CALCULATION_H
#define INTEGRAL_CALCULATION_H

void countIntegral(int a, int b, TReal eps, Function f, int maxIterations, int method);
void methodTrapezium(TReal a, TReal b, Function f, int n, TReal *s);
void methodSimson(TReal a, TReal b, Function f, int n, TReal *s);
void method38(TReal a, TReal b, Function f, int n, TReal *s);

#endif // INTEGRAL_CALCULATION_H
