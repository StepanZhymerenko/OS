#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define MAX_THREADS 100

int *result_array; // Глобальний масив для зберігання результатів
int num_threads;   // Кількість потоків
int filled_count = 0; // Лічильник для відстеження заповнення масиву

pthread_mutex_t mutex; // М’ютекс для синхронізації

// Функція для розрахункових потоків
void* worker_thread(void *arg) {
    int thread_id = *(int*)arg;
    int sleep_time = thread_id;

    // Виводимо інформацію про початок роботи потоку
    printf("Потік %d починає роботу. Засинає на %d секунд.\n", thread_id, sleep_time);
    sleep(sleep_time);

    // Генеруємо випадкове число в діапазоні [1, 10]
    int random_value = (rand() % 10) + 1;

    // Заносимо число у відповідну комірку масиву
    pthread_mutex_lock(&mutex);
    result_array[thread_id] = random_value;
    filled_count++;
    printf("Потік %d прокинувся, згенерував число %d та заніс його до масиву.\n", thread_id, random_value);
    pthread_mutex_unlock(&mutex);

    // Засинаємо ще раз на згенеровану кількість секунд
    printf("Потік %d засинає ще раз на %d секунд.\n", thread_id, random_value);
    sleep(random_value);

    // Завершення потоку
    printf("Потік %d завершив роботу.\n", thread_id);
    return NULL;
}

// Функція для від'єднаного потоку, який постійно перевіряє значення в масиві
void* monitor_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // Виводимо всі значення з масиву з поясненням
        printf("=== Поточний стан масиву на цей момент: ===\n");
        for (int i = 0; i < num_threads; i++) {
            printf("Індекс %d: %d\n", i, result_array[i]);
        }
        printf("============================================\n");

        // Якщо масив повністю заповнений, завершуємо потік
        if (filled_count == num_threads) {
            pthread_mutex_unlock(&mutex);
            printf("Від'єднаний потік завершив роботу, оскільки масив заповнено.\n");
            break;
        }

        pthread_mutex_unlock(&mutex);
        sleep(1); // Затримка у 1 секунду перед наступним виведенням
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Використання: %s <кількість_потоків>\n", argv[0]);
        return 1;
    }

    num_threads = atoi(argv[1]);
    if (num_threads <= 0 || num_threads > MAX_THREADS) {
        fprintf(stderr, "Неправильна кількість потоків. Введіть число від 1 до %d.\n", MAX_THREADS);
        return 1;
    }

    result_array = (int*) malloc(num_threads * sizeof(int));
    for (int i = 0; i < num_threads; i++) {
        result_array[i] = 0; // Ініціалізація масиву нулями
    }

    pthread_t threads[num_threads];
    pthread_t monitor;
    pthread_mutex_init(&mutex, NULL);

    srand(time(NULL)); // Ініціалізація генератора випадкових чисел

    // Створення від'єднаного моніторного потоку
    printf("Запуск від'єднаного потоку монітора...\n");
    pthread_create(&monitor, NULL, monitor_thread, NULL);
    pthread_detach(monitor);

    // Створення розрахункових потоків
    for (int i = 0; i < num_threads; i++) {
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        printf("Запуск потоку %d...\n", i);
        pthread_create(&threads[i], NULL, worker_thread, arg);
    }

    // Очікування завершення всіх розрахункових потоків
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Очищення
    free(result_array);
    pthread_mutex_destroy(&mutex);

    printf("Програма завершена.\n");
    return 0;
}
