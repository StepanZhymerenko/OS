#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define DEFAULT_ARRAY_SIZE 10
#define DEFAULT_WRITERS 2
#define DEFAULT_READERS 4
#define DEFAULT_RUN_TIME 10

int *array;                        // Масив даних
int array_size = DEFAULT_ARRAY_SIZE; // Розмір масиву
int num_writers = DEFAULT_WRITERS;    // Кількість потоків-письменників
int num_readers = DEFAULT_READERS;    // Кількість потоків-читачів
int run_time = DEFAULT_RUN_TIME;      // Час роботи програми (в секундах)
pthread_rwlock_t rwlock;            // Блокування для читання-запису

void* writer_function(void* arg) {
    int writer_id = *(int*)arg;  // Отримуємо ідентифікатор письменника
    while (1) {
        int index = rand() % array_size;
        int value = rand() % 100;  // Записуємо значення в діапазоні 0-99
        
        pthread_rwlock_wrlock(&rwlock); // Блокування для запису
        array[index] = value;
        printf("Writer %d wrote array[%d] = %d\n", writer_id, index, value);
        pthread_rwlock_unlock(&rwlock); // Розблокування
        usleep(100000);  // Затримка 100 мс
    }
    return NULL;
}

void* reader_function(void* arg) {
    while (1) {
        int index = rand() % array_size;

        pthread_rwlock_rdlock(&rwlock); // Блокування для читання
        int value = array[index];
        pthread_rwlock_unlock(&rwlock); // Розблокування
        printf("Reader read array[%d] = %d\n", index, value);
        usleep(100000);  // Затримка 100 мс
    }
    return NULL;
}

void* monitor_function(void* arg) {
    while (1) {
        pthread_rwlock_rdlock(&rwlock); // Блокування для читання
        printf("Array state: ");
        for (int i = 0; i < array_size; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
        pthread_rwlock_unlock(&rwlock); // Розблокування
        sleep(1);  // Виводимо стан масиву раз на секунду
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    // Обробка параметрів командного рядка
    int opt;
    while ((opt = getopt(argc, argv, "s:w:r:t:")) != -1) {
        switch (opt) {
            case 's':
                array_size = atoi(optarg);
                break;
            case 'w':
                num_writers = atoi(optarg);
                break;
            case 'r':
                num_readers = atoi(optarg);
                break;
            case 't':
                run_time = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-s array_size] [-w writers] [-r readers] [-t run_time]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Ініціалізація масиву і блокування
    array = (int*)malloc(array_size * sizeof(int));
    for (int i = 0; i < array_size; i++) {
        array[i] = 0;
    }
    pthread_rwlock_init(&rwlock, NULL);
    srand(time(NULL));

    // Створення потоків
    pthread_t writers[num_writers];
    pthread_t readers[num_readers];
    pthread_t monitor;
    int writer_ids[num_writers];

    for (int i = 0; i < num_writers; i++) {
        writer_ids[i] = i + 1;  // Ідентифікатор для кожного письменника
        pthread_create(&writers[i], NULL, writer_function, &writer_ids[i]);
    }
    for (int i = 0; i < num_readers; i++) {
        pthread_create(&readers[i], NULL, reader_function, NULL);
    }
    pthread_create(&monitor, NULL, monitor_function, NULL);

    // Чекаємо завершення часу роботи
    sleep(run_time);

    // Завершення роботи потоків
    for (int i = 0; i < num_writers; i++) {
        pthread_cancel(writers[i]);
    }
    for (int i = 0; i < num_readers; i++) {
        pthread_cancel(readers[i]);
    }
    pthread_cancel(monitor);

    // Звільнення ресурсів
    pthread_rwlock_destroy(&rwlock);
    free(array);

    printf("Програма завершила роботу.\n");
    return 0;
}
