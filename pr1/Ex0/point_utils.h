#ifndef POINT_UTILS_H
#define POINT_UTILS_H

struct PointWithMass {
    int x;
    int y;
    int z;
    float mass;
};

void printPWM(struct PointWithMass p);
void printPWMArray(struct PointWithMass points[], int size);
void initializePWM(struct PointWithMass *point, int x, int y, int z, float mass);
int findMinMassPWMIndex(struct PointWithMass points[], int size);
double calculateDistance(struct PointWithMass p1, struct PointWithMass p2);
int findNearestPointIndex(struct PointWithMass points[], int size, int excludeIndex);
void removePoint(struct PointWithMass points[], int *size, int removeIndex);

#endif
