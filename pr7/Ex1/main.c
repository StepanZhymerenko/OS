#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

long shared_var = 0;

typedef struct {
    int operations;
} ThreadData;

// Функція для збільшення змінної
void* increment(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (int i = 0; i < data->operations; i++) {
        shared_var++;  // Збільшення без блокування
    }
    return NULL;
}

// Функція для зменшення змінної
void* decrement(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (int i = 0; i < data->operations; i++) {
        shared_var--;  // Зменшення без блокування
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    int num_threads = 2;
    int operations = 1000;
    int repetitions = 1;

    int opt;
    while ((opt = getopt(argc, argv, "t:o:r:")) != -1) {
        switch (opt) {
            case 't':
                num_threads = atoi(optarg);
                break;
            case 'o':
                operations = atoi(optarg);
                break;
            case 'r':
                repetitions = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-t num_threads] [-o operations] [-r repetitions]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    printf("Кількість пар потоків: %d\n", num_threads);
    printf("Кількість операцій: %d\n", operations);
    printf("Кількість повторень: %d\n", repetitions);

    pthread_t threads[num_threads * 2];
    ThreadData data = { .operations = operations };

    // Основний цикл для багаторазового виконання дій
    for (int rep = 0; rep < repetitions; rep++) {
        shared_var = 0;  // Скидаємо значення змінної перед кожним запуском

        printf("\nПовторення %d:\n", rep + 1);
        printf("Початкове значення змінної: %ld\n", shared_var);

        // Створення пар потоків
        for (int i = 0; i < num_threads; i++) {
            pthread_create(&threads[i * 2], NULL, increment, &data);
            pthread_create(&threads[i * 2 + 1], NULL, decrement, &data);
        }

        // Очікування завершення роботи всіх потоків
        for (int i = 0; i < num_threads * 2; i++) {
            pthread_join(threads[i], NULL);
        }

        printf("Фінальне значення змінної: %ld\n", shared_var);
    }

    return 0;
}
