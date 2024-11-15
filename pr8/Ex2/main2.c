#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 5    // Розмір буфера
#define NUM_PRODUCERS 3  // Кількість виробників
#define NUM_CONSUMERS 2  // Кількість споживачів

int buffer[BUFFER_SIZE];
int count = 0, in = 0, out = 0; // Лічильник елементів, позиції запису та зчитування

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_not_full = PTHREAD_COND_INITIALIZER;

volatile int stop = 0; // Флаг завершення роботи потоків

void* producer(void* param) {
    int id = *((int*)param);
    while (!stop) {
        int item = rand() % 100; // Генеруємо випадкове число
        usleep(rand() % 200000); // Затримка для імітації роботи

        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE && !stop) { // Чекаємо, якщо буфер заповнений
            pthread_cond_wait(&buffer_not_full, &mutex);
        }

        if (stop) { // Якщо роботу завершено
            pthread_mutex_unlock(&mutex);
            break;
        }

        buffer[in] = item;
        printf("Producer %d produced: %d\n", id, item);
        in = (in + 1) % BUFFER_SIZE;
        count++;

        pthread_cond_signal(&buffer_not_empty); // Сповіщаємо споживачів
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* consumer(void* param) {
    int id = *((int*)param);
    while (!stop || count > 0) { // Споживаємо, доки є дані
        pthread_mutex_lock(&mutex);

        while (count == 0 && !stop) { // Чекаємо, якщо буфер порожній
            pthread_cond_wait(&buffer_not_empty, &mutex);
        }

        if (count == 0 && stop) { // Якщо буфер порожній і завершення роботи
            pthread_mutex_unlock(&mutex);
            break;
        }

        int item = buffer[out];
        printf("Consumer %d consumed: %d\n", id, item);
        out = (out + 1) % BUFFER_SIZE;
        count--;

        pthread_cond_signal(&buffer_not_full); // Сповіщаємо виробників
        pthread_mutex_unlock(&mutex);

        usleep(rand() % 300000); // Затримка для імітації роботи
    }
    return NULL;
}

int main() {
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];
    int producer_ids[NUM_PRODUCERS];
    int consumer_ids[NUM_CONSUMERS];

    srand(time(NULL)); // Ініціалізація генератора випадкових чисел

    // Створюємо потоки виробників
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        producer_ids[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
    }

    // Створюємо потоки споживачів
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        consumer_ids[i] = i + 1;
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }

    // Головний потік контролює час виконання
    sleep(20);
    stop = 1;

    // Будимо всі потоки, щоб завершилися
    pthread_cond_broadcast(&buffer_not_empty);
    pthread_cond_broadcast(&buffer_not_full);

    // Чекаємо завершення потоків виробників
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    // Чекаємо завершення потоків споживачів
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Очистка ресурсів
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&buffer_not_empty);
    pthread_cond_destroy(&buffer_not_full);

    printf("Program completed successfully.\n");
    return 0;
}
