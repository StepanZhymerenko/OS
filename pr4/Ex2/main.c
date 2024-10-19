#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

// Макровизначення для часу виконання у секундах
#define SECONDS 5

int main() {
    // Лічильники для батьківського та дочірнього процесів
    int parent_counter = 0, child_counter = 0;
    
    // Отримуємо поточний час (в UNIX timestamp)
    time_t start_time = time(NULL);
    
    // Створюємо процес-нащадок
    pid_t pid = fork();
    
    if (pid == -1) {
        // Помилка при створенні процесу
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Дочірній процес
        while (time(NULL) - start_time < SECONDS) {
            child_counter++; // Збільшуємо лічильник дочірнього процесу
        }
        printf("Child process completed %d iterations in %d seconds.\n", child_counter, SECONDS);
    } else {
        // Батьківський процес
        while (time(NULL) - start_time < SECONDS) {
            parent_counter++; // Збільшуємо лічильник батьківського процесу
        }
        printf("Parent process completed %d iterations in %d seconds.\n", parent_counter, SECONDS);
    }

    return 0;
}
