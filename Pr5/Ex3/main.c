#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

typedef struct {
    char *message;   // Повідомлення для виведення
    int repeat_count; // Кількість повторень
} PrintParams;

typedef struct {
    int range_min;     // Мінімальне значення діапазону
    int range_max;     // Максимальне значення діапазону
    int random_count;  // Кількість випадкових чисел для генерації
    int stop_value;    // Число для зупинки потоку
} RandomParams;

// Функція для першого потоку: виведення повідомлення
void* print_thread_function(void* arg) {
    PrintParams* params = (PrintParams*)arg;
    for (int i = 1; i <= params->repeat_count; i++) {
        printf("Print Thread: %s - Iteration %d\n", params->message, i);
        sleep(1); // Затримка в 1 секунду між виведеннями
    }
    return NULL;
}

// Функція для другого потоку: генерація випадкових чисел
void* random_thread_function(void* arg) {
    RandomParams* params = (RandomParams*)arg;
    srand(time(NULL)); // Ініціалізація генератора випадкових чисел

    for (int i = 1; i <= params->random_count; i++) {
        int random_number = params->range_min + rand() % (params->range_max - params->range_min + 1);
        printf("Random Thread: Generated number %d - Iteration %d\n", random_number, i);

        if (random_number == params->stop_value) {
            printf("Random Thread: Stop value %d generated. Exiting early.\n", params->stop_value);
            return NULL;
        }
        sleep(1); // Затримка в 1 секунду між генерацією чисел
    }
    return NULL;
}

int main() {
    pthread_t print_thread, random_thread;

    // Параметри для потоку, що виводить повідомлення
    PrintParams print_params = {"Hello from Print Thread", 5};

    // Параметри для потоку, що генерує випадкові числа
    RandomParams random_params = {1, 10, 8, 5};

    // Створення потоків
    if (pthread_create(&print_thread, NULL, print_thread_function, &print_params) != 0) {
        perror("Failed to create print thread");
        return 1;
    }
    if (pthread_create(&random_thread, NULL, random_thread_function, &random_params) != 0) {
        perror("Failed to create random thread");
        return 1;
    }

    // Очікування завершення потоків
    pthread_join(print_thread, NULL);
    pthread_join(random_thread, NULL);

    // Повідомлення від основного потоку після завершення всіх нащадків
    printf("Main Thread: All child threads have finished.\n");

    return 0;
}
