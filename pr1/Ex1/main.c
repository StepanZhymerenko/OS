#include <stdio.h>
#include <stdlib.h>
#include "taylor.h"
#include "derivative.h"

int main() {
    system("chcp 65001");
    double a, b, epsilon;
    int n;

    printf("Введіть a: ");
    scanf("%lf", &a);
    printf("Введіть b: ");
    scanf("%lf", &b);
    printf("Введіть кількість сегментів n: ");
    scanf("%d", &n);
    printf("Введіть точність epsilon: ");
    scanf("%lf", &epsilon);

    double length = curve_length(a, b, n, epsilon);
    printf("Довжина кривої: %lf\n", length);

    return 0;
}
