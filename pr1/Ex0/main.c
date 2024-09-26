#include <stdio.h>
#include <stdlib.h>
#include "point_utils.h"
#include "process_points.h"

int main(void) {
    int N = 5;
    struct PointWithMass *points = malloc(sizeof(struct PointWithMass) * N);

    initializePWM(&points[0], 0, 0, 0, 30.0);
    initializePWM(&points[1], 0, 0, 2, 10.0);
    initializePWM(&points[2], 1, 1, 3, 4350.0);
    initializePWM(&points[3], 1, 1, 4, 67.0);
    initializePWM(&points[4], 2, 2, 2, 500.0);

    printf("Початкові точки:\n");
    printPWMArray(points, N);

    processPoints(points, &N);

    printf("\nЗалишилась лише одна точка:\n");
    printPWM(points[0]);

    free(points);
    return 0;
}
