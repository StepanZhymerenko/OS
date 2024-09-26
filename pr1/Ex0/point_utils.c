#include <stdio.h>
#include <math.h>
#include "point_utils.h"

void printPWM(struct PointWithMass p) {
    printf("Point: coordinates(%d, %d, %d), mass: %.2f\n", p.x, p.y, p.z, p.mass);
}

void printPWMArray(struct PointWithMass points[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Point %d: coordinates(%d, %d, %d), mass: %.2f\n", i, points[i].x, points[i].y, points[i].z, points[i].mass);
    }
}

void initializePWM(struct PointWithMass *point, int x, int y, int z, float mass) {
    point->x = x;
    point->y = y;
    point->z = z;
    point->mass = mass;
}

int findMinMassPWMIndex(struct PointWithMass points[], int size) {
    int minIndex = 0;
    float minMass = points[0].mass;
    for (int i = 1; i < size; i++) {
        if (points[i].mass < minMass) {
            minIndex = i;
            minMass = points[i].mass;
        }
    }
    return minIndex;
}

double calculateDistance(struct PointWithMass p1, struct PointWithMass p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
}

int findNearestPointIndex(struct PointWithMass points[], int size, int excludeIndex) {
    double minDistance = INFINITY;
    int nearestIndex = -1;
    for (int i = 0; i < size; i++) {
        if (i != excludeIndex) {
            double distance = calculateDistance(points[excludeIndex], points[i]);
            if (distance < minDistance) {
                minDistance = distance;
                nearestIndex = i;
            }
        }
    }
    return nearestIndex;
}

void removePoint(struct PointWithMass points[], int *size, int removeIndex) {
    for (int i = removeIndex; i < *size - 1; i++) {
        points[i] = points[i + 1];
    }
    (*size)--;
}
