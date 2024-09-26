#include "taylor.h"
#include <math.h>

double taylor_sin(double x, double epsilon) {
    double term = x;
    double sum = term;
    int n = 1;
    while (fabs(term) >= epsilon) {
        term *= -x * x / ((2 * n) * (2 * n + 1));
        sum += term;
        n++;
    }
    return sum;
}

double taylor_cos(double x, double epsilon) {
    double term = 1.0;
    double sum = term;
    int n = 1;
    while (fabs(term) >= epsilon) {
        term *= -x * x / ((2 * n - 1) * (2 * n));
        sum += term;
        n++;
    }
    return sum;
}
