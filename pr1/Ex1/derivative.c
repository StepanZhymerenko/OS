#include "taylor.h"
#include "derivative.h"
#include <math.h>

double derivative_f(double x, double epsilon) {
    double sin_x = taylor_sin(x, epsilon);
    double cos_x = taylor_cos(x, epsilon);
    double numerator = 2 * sin_x * taylor_cos(x, epsilon); // похідна від sin^2(x)
    double denominator = 1 + cos_x * cos_x * cos_x; // похідна від 1 + cos^3(x)
    return numerator / denominator;
}

double curve_length(double a, double b, int n, double epsilon) {
    double h = (b - a) / n;
    double length = 0.0;

    for (int i = 0; i < n; i++) {
        double x1 = a + i * h;
        double x2 = a + (i + 1) * h;
        double df1 = derivative_f(x1, epsilon);
        double df2 = derivative_f(x2, epsilon);
        length += sqrt(1 + df1 * df1) * h;
    }

    return length;
}
