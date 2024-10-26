#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

// Структура для зберігання параметрів потоку
typedef struct {
    char name[20];  // Ім'я потоку
    char str[50];   // Базова частина рядка для виведення
    int num;        // Кількість повторень рядка
} ThreadParams;

// Функція, яку виконують потоки
void* thread_function(void* arg) {
    ThreadParams* params = (ThreadParams*)arg;

    for (int i = 1; i <= params->num; i++) {
        printf("Thread %s. %s %d\n", params->name, params->str, i);
        sleep(1); // Затримка в 1 секунду між виведеннями
    }
    return NULL;
}

int main() {
    pthread_t threads[4];
    ThreadParams params[4] = {
        {"Thread 1", "Message from Thread 1", 5},
        {"Thread 2", "Message from Thread 2", 3},
        {"Thread 3", "Message from Thread 3", 4},
        {"Thread 4", "Message from Thread 4", 6}
    };

    // Створення потоків
    for (int i = 0; i < 4; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, &params[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Очікування завершення кожного потоку
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
