#include <stdio.h>
#include "student.h"

void printStudents(Student students[], int n) {
    printf("Список студентів:\n");
    for (int i = 0; i < n; i++) {
        printf("Ім'я: %s, Група: %d, Веб-технології: %d, Українська мова: %d, Проектування інф. систем: %d\n", 
               students[i].name, students[i].group, students[i].web_tech, students[i].ukr_language, students[i].project_inf_systems);
    }
}

void printDebtors(Student students[], int n) {
    printf("Студенти з заборгованістю:\n");
    for (int i = 0; i < n; i++) {
        if (students[i].web_tech < 50 || students[i].ukr_language < 50 || students[i].project_inf_systems < 50) {
            printf("%s\n", students[i].name);
        }
    }
}

void printExcellentOrGoodPercentage(Student students[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (students[i].web_tech >= 75 && students[i].ukr_language >= 75 && students[i].project_inf_systems >= 75) {
            count++;
        }
    }
    printf("Відсоток студентів, які склали всі іспити на відмінно або добре: %.2f%%\n", (count * 100.0) / n);
}

void printBestSubject(Student students[], int n) {
    int total_web_tech = 0, total_ukr_language = 0, total_project_inf_systems = 0;
    for (int i = 0; i < n; i++) {
        total_web_tech += students[i].web_tech;
        total_ukr_language += students[i].ukr_language;
        total_project_inf_systems += students[i].project_inf_systems;
    }
    if (total_web_tech >= total_ukr_language && total_web_tech >= total_project_inf_systems) {
        printf("Предмет, зданий найкраще: Веб-технології\n");
    } else if (total_ukr_language >= total_web_tech && total_ukr_language >= total_project_inf_systems) {
        printf("Предмет, зданий найкраще: Українська мова\n");
    } else {
        printf("Предмет, зданий найкраще: Проектування інформаційних систем\n");
    }
}

void printWorstGroup(Student students[], int n) {
    int group_sum[4] = {0};
    int group_count[4] = {0};

    for (int i = 0; i < n; i++) {
        group_sum[students[i].group - 1] += (students[i].web_tech + students[i].ukr_language + students[i].project_inf_systems);
        group_count[students[i].group - 1]++;
    }

    int worst_group = 0;
    double worst_average = (double)group_sum[0] / group_count[0];

    for (int i = 1; i < 4; i++) {
        double average = (double)group_sum[i] / group_count[i];
        if (average < worst_average) {
            worst_average = average;
            worst_group = i;
        }
    }

    printf("Група з найгіршою успішністю: %d\n", worst_group + 1);
}
