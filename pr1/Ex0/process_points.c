#include <stdio.h>
#include "point_utils.h"
#include "process_points.h"

void processPoints(struct PointWithMass points[], int *size) {
    while (*size > 1) {
        // Знаходимо точку з найменшою масою
        int minMassIndex = findMinMassPWMIndex(points, *size);
        printf("\nТочка з найменшою масою: %d\n", minMassIndex);
        printPWM(points[minMassIndex]);

        // Знаходимо найближчу точку
        int nearestIndex = findNearestPointIndex(points, *size, minMassIndex);
        printf("Найближча точка до неї: %d\n", nearestIndex);
        printPWM(points[nearestIndex]);

        // Передаємо масу найближчій точці
        points[nearestIndex].mass += points[minMassIndex].mass;

        // Видаляємо точку з найменшою масою
        removePoint(points, size, minMassIndex);

        // Виводимо новий стан масивів
        printf("\nПоточні точки після передачі маси:\n");
        printPWMArray(points, *size);
    }
}
