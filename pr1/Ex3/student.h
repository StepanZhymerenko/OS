#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME_LEN 12
#define MAX_STUDENTS 30

typedef struct {
    char name[MAX_NAME_LEN + 1];
    int group;
    int web_tech;
    int ukr_language;
    int project_inf_systems;
} Student;

// Function declarations
void printStudents(Student students[], int n);
void printDebtors(Student students[], int n);
void printExcellentOrGoodPercentage(Student students[], int n);
void printBestSubject(Student students[], int n);
void printWorstGroup(Student students[], int n);

#endif // STUDENT_H
