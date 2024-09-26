#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main() {
    system("chcp 65001");

    Student students[MAX_STUDENTS] = {
        {"Ivanov", 1, 80, 90, 85},
        {"Petrenko", 2, 55, 65, 75},
        {"Shevchenko", 1, 100, 95, 90},
        {"Koval", 3, 70, 50, 65},
        {"Tkachenko", 4, 40, 45, 50}
    };

    int n = 5;

    printStudents(students, n);
    printDebtors(students, n);
    printExcellentOrGoodPercentage(students, n);
    printBestSubject(students, n);
    printWorstGroup(students, n);

    return 0;
}
