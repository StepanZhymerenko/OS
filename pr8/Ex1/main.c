#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 5    // Розмір буфера
#define NUM_PRODUCERS 3  // Кількість виробників
#define NUM_CONSUMERS 2  // Кількість споживачів

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
volatile int stop = 0; // Флаг для завершення потоків
volatile int items_remaining = 0; // Елементи, що залишилися у буфері

sem_t empty_slots;  // Семафор для відстеження порожніх місць у буфері
sem_t full_slots;   // Семафор для відстеження заповнених місць у буфері
pthread_mutex_t buffer_mutex; // М'ютекс для синхронізації доступу до буфера

void* producer(void* param) {
    int id = *((int*)param);
    while (!stop) {
        int item = rand() % 100; // Генеруємо випадковий елемент
        sem_wait(&empty_slots); // Чекаємо на вільний слот
        pthread_mutex_lock(&buffer_mutex); // Входимо у критичну секцію

        if (stop) { // Перевіряємо флаг завершення
            pthread_mutex_unlock(&buffer_mutex);
            sem_post(&empty_slots);
            break;
        }

        buffer[in] = item;
        items_remaining++; // Збільшуємо кількість елементів у буфері
        printf("Producer %d produced: %d\n", id, item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&buffer_mutex); // Виходимо з критичної секції
        sem_post(&full_slots); // Збільшуємо кількість заповнених слотів
        sleep(rand() % 3 + 1); // Імітація затримки
    }
    return NULL;
}

void* consumer(void* param) {
    int id = *((int*)param);
    while (1) {
        if (stop && items_remaining == 0) { // Завершення, якщо всі дані оброблено
            break;
        }
        sem_wait(&full_slots); // Чекаємо на заповнений слот
        pthread_mutex_lock(&buffer_mutex); // Входимо у критичну секцію

        if (items_remaining == 0 && stop) { // Перевіряємо залишки у буфері
            pthread_mutex_unlock(&buffer_mutex);
            sem_post(&full_slots);
            break;
        }

        int item = buffer[out];
        items_remaining--; // Зменшуємо кількість елементів у буфері
        printf("Consumer %d consumed: %d\n", id, item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&buffer_mutex); // Виходимо з критичної секції
        sem_post(&empty_slots); // Збільшуємо кількість вільних слотів
        sleep(rand() % 3 + 1); // Імітація затримки
    }
    return NULL;
}

int main() {
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];
    int producer_ids[NUM_PRODUCERS];
    int consumer_ids[NUM_CONSUMERS];

    // Ініціалізуємо генератор випадкових чисел
    srand(time(NULL));

    // Ініціалізуємо семафори та м'ютекс
    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);
    pthread_mutex_init(&buffer_mutex, NULL);

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
    stop = 1; // Завершення виробників

    // Вивільняємо споживачів
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        sem_post(&full_slots);
    }

    // Чекаємо завершення потоків виробників
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    // Чекаємо завершення потоків споживачів
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Виводимо залишковий стан буфера
    printf("Remaining items in buffer: %d\n", items_remaining);

    // Очистка ресурсів
    pthread_mutex_destroy(&buffer_mutex);
    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);

    printf("Program completed successfully.\n");
    return 0;
}
