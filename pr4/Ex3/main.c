#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h> // для функції wait

int main() {
    int local_var = 0;  // Локальна змінна
    pid_t pid1, pid2;

    // Перший fork: створює перший підпроцес
    pid1 = fork();

    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // Перший підпроцес
        local_var++;  // Збільшення локальної змінної
        printf("Child1 (PID: %d, PPID: %d) | Local var: %d | Address: %p\n", getpid(), getppid(), local_var, &local_var);

        // Створюємо перший дочірній процес для першого підпроцесу
        pid_t pid1_1 = fork();

        if (pid1_1 < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid1_1 == 0) {
            // Дочірній процес першого підпроцесу
            local_var++;
            printf("Child1_1 (PID: %d, PPID: %d) | Local var: %d | Address: %p\n", getpid(), getppid(), local_var, &local_var);
            exit(0);  // Завершення першого дочірнього процесу
        }

        // Створюємо другий дочірній процес для першого підпроцесу
        pid_t pid1_2 = fork();

        if (pid1_2 < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid1_2 == 0) {
            // Другий дочірній процес першого підпроцесу
            local_var++;
            printf("Child1_2 (PID: %d, PPID: %d) | Local var: %d | Address: %p\n", getpid(), getppid(), local_var, &local_var);
            exit(0);  // Завершення другого дочірнього процесу
        }

        // Очікуємо завершення обох дочірніх процесів
        wait(NULL);  // Очікуємо завершення першого дочірнього процесу
        wait(NULL);  // Очікуємо завершення другого дочірнього процесу
        exit(0);  // Завершення першого підпроцесу
    } else {
        // Батьківський процес створює другий підпроцес
        pid2 = fork();

        if (pid2 < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) {
            // Другий підпроцес
            local_var++;  // Збільшення локальної змінної
            printf("Child2 (PID: %d, PPID: %d) | Local var: %d | Address: %p\n", getpid(), getppid(), local_var, &local_var);

            // Створюємо перший дочірній процес для другого підпроцесу
            pid_t pid2_1 = fork();

            if (pid2_1 < 0) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid2_1 == 0) {
                // Дочірній процес другого підпроцесу
                local_var++;
                printf("Child2_1 (PID: %d, PPID: %d) | Local var: %d | Address: %p\n", getpid(), getppid(), local_var, &local_var);
                exit(0);  // Завершення першого дочірнього процесу
            }

            // Створюємо другий дочірній процес для другого підпроцесу
            pid_t pid2_2 = fork();

            if (pid2_2 < 0) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid2_2 == 0) {
                // Другий дочірній процес другого підпроцесу
                local_var++;
                printf("Child2_2 (PID: %d, PPID: %d) | Local var: %d | Address: %p\n", getpid(), getppid(), local_var, &local_var);
                exit(0);  // Завершення другого дочірнього процесу
            }

            // Очікуємо завершення обох дочірніх процесів
            wait(NULL);  // Очікуємо завершення першого дочірнього процесу
            wait(NULL);  // Очікуємо завершення другого дочірнього процесу
            exit(0);  // Завершення другого підпроцесу
        } else {
            // Батьківський процес виводить інформацію про створені процеси
            printf("Parent (PID: %d) created Child1 (PID: %d) and Child2 (PID: %d)\n", getpid(), pid1, pid2);

            // Очікуємо завершення обох підпроцесів
            wait(NULL);  // Очікуємо завершення першого підпроцесу
            wait(NULL);  // Очікуємо завершення другого підпроцесу
        }
    }

    return 0;
}
