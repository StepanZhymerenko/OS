#include <math.h> // для fabs()
#include "utils.h"

double calculate_average(double array[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += array[i];
    }
    return sum / n;
}

int count_greater_than_average(double array[], int n, double average) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (array[i] > average) {
            count++;
        }
    }
    return count;
}

double sum_abs_after_first_negative(double array[], int n) {
    int first_negative_index = -1;
    double abs_sum = 0.0;

    for (int i = 0; i < n; i++) {
        if (array[i] < 0) {
            first_negative_index = i;
            break;
        }
    }

    if (first_negative_index != -1 && first_negative_index < n - 1) {
        for (int i = first_negative_index + 1; i < n; i++) {
            abs_sum += fabs(array[i]);
        }
    }

    return abs_sum;
}
