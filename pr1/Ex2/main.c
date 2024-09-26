#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

int main() {
    system("chcp 65001");
    int n;

    printf("Введіть кількість елементів масиву n: ");
    scanf("%d", &n);

    double array[n];

    printf("Введіть елементи масиву:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &array[i]);
    }

    double average = calculate_average(array, n);
    int count = count_greater_than_average(array, n, average);
    double abs_sum = sum_abs_after_first_negative(array, n);

    printf("Кількість елементів, що більші за середнє значення: %d\n", count);
    printf("Сума абсолютних значень елементів після першого від'ємного: %lf\n", abs_sum);

    return 0;
}
