#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

volatile int shared_data = -1; // Глобальна змінна для обміну даними (-1 означає, що даних немає)

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t data_available = PTHREAD_COND_INITIALIZER; // Умовна змінна для сигналізації про наявність даних
pthread_cond_t data_consumed = PTHREAD_COND_INITIALIZER; // Умовна змінна для сигналізації про споживання даних

volatile int stop = 0; // Флаг завершення роботи потоків

// Функція для отримання поточного часу
void log_time(const char* thread_type, int id, const char* message, int iteration, int value) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts); // Отримуємо поточний час
    printf("[%ld.%09ld] %s %d %s (Iteration: %d, Value: %d)\n", 
           ts.tv_sec, ts.tv_nsec, thread_type, id, message, iteration, value);
}

void* producer(void* param) {
    int id = *((int*)param);
    int iteration = 0; // Лічильник ітерацій
    while (!stop) {
        int item = rand() % 100; // Генеруємо випадкове число
        usleep(rand() % 200000); // Затримка для імітації роботи

        pthread_mutex_lock(&mutex);

        // Чекаємо, поки споживач не забере попереднє значення
        while (shared_data != -1 && !stop) {
            pthread_cond_wait(&data_consumed, &mutex);
        }

        if (stop) { // Якщо завершення роботи
            pthread_mutex_unlock(&mutex);
            break;
        }

        shared_data = item; // Записуємо нове значення в глобальну змінну
        iteration++;
        log_time("Producer", id, "produced", iteration, item);

        pthread_cond_signal(&data_available); // Сигналізуємо споживачу про наявність нових даних
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* consumer(void* param) {
    int id = *((int*)param);
    int iteration = 0; // Лічильник ітерацій
    while (!stop) {
        pthread_mutex_lock(&mutex);

        // Чекаємо, поки виробник не згенерує нове значення
        while (shared_data == -1 && !stop) {
            pthread_cond_wait(&data_available, &mutex);
        }

        if (stop) { // Якщо завершення роботи
            pthread_mutex_unlock(&mutex);
            break;
        }

        int item = shared_data; // Зчитуємо значення
        shared_data = -1;       // Очищуємо глобальну змінну
        iteration++;
        log_time("Consumer", id, "consumed", iteration, item);

        pthread_cond_signal(&data_consumed); // Сигналізуємо виробнику, що дані спожито
        pthread_mutex_unlock(&mutex);

        usleep(rand() % 300000); // Затримка для імітації роботи
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    srand(time(NULL)); // Ініціалізація генератора випадкових чисел

    int producer_id = 1;
    int consumer_id = 1;

    // Створюємо потоки
    pthread_create(&producer_thread, NULL, producer, &producer_id);
    pthread_create(&consumer_thread, NULL, consumer, &consumer_id);

    // Головний потік контролює час виконання
    sleep(20);
    stop = 1;

    // Будимо всі потоки, щоб завершилися
    pthread_cond_broadcast(&data_available);
    pthread_cond_broadcast(&data_consumed);

    // Чекаємо завершення потоків
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Очистка ресурсів
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&data_available);
    pthread_cond_destroy(&data_consumed);

    printf("Program completed successfully.\n");
    return 0;
}
