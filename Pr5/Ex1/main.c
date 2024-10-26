#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Функція для нового потоку
void* child_thread_function(void* arg) {
    for (int i = 1; i <= 10; i++) {
        printf("Child Thread. Iteration: %d\n", i);
        sleep(1); // Затримка в секундах
    }
    return NULL;
}

int main() {
    pthread_t child_thread;

    // Створення нового потоку
    if (pthread_create(&child_thread, NULL, child_thread_function, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // Основний потік
    for (int i = 1; i <= 10; i++) {
        printf("Main Thread. Iteration: %d\n", i);
        sleep(1); // Затримка в секундах
    }

    // Очікування завершення нового потоку
    pthread_join(child_thread, NULL);

    return 0;
}
