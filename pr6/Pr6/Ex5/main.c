#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

// Структура для зберігання даних кожного потоку
typedef struct {
    int thread_id;
    char message[100]; 
} thread_data_t;

pthread_mutex_t print_mutex; // М'ютекс для синхронізації виводу

// Функція, яка буде виконуватись кожним потоком
void* thread_function(void* arg) {
    // Витягуємо дані для поточного потоку
    thread_data_t *data = (thread_data_t *)arg;

    // Ініціалізуємо генератор випадкових чисел для цього потоку
    srand(time(NULL) + data->thread_id);

    // Випадкове число рядків для виведення
    int lines = rand() % 10 + 1; // Від 1 до 10 рядків

    // Виводимо кількість рядків, які потік збирається вивести
    pthread_mutex_lock(&print_mutex);
    printf("Потік %d збирається вивести %d рядків.\n", data->thread_id, lines);
    pthread_mutex_unlock(&print_mutex);

    for (int i = 0; i < lines; i++) {
        // Генеруємо випадкове число у діапазоні [1, 100]
        int random_number = rand() % 100 + 1;
        
        // Синхронізований вивід за допомогою м'ютекса
        pthread_mutex_lock(&print_mutex);
        printf("Потік %d: %s - Випадкове число: %d\n", data->thread_id, data->message, random_number);
        pthread_mutex_unlock(&print_mutex);

        // Затримка, щоб зробити вивід наочнішим
        sleep(1);
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Використання: %s <кількість_потоків>\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]);
    if (num_threads <= 0) {
        fprintf(stderr, "Кількість потоків має бути додатнім числом.\n");
        return 1;
    }

    pthread_t threads[num_threads];
    thread_data_t thread_data[num_threads];

    // Ініціалізація генератора випадкових чисел
    srand(time(NULL));

    // Ініціалізуємо м'ютекс для синхронізації виводу
    pthread_mutex_init(&print_mutex, NULL);

    // Створюємо потоки-нащадки
    for (int i = 0; i < num_threads; i++) {
        // Заповнюємо дані для поточного потоку
        thread_data[i].thread_id = i;
        snprintf(thread_data[i].message, sizeof(thread_data[i].message), "Повідомлення від потоку %d", i);

        // Створюємо потік
        if (pthread_create(&threads[i], NULL, thread_function, &thread_data[i]) != 0) {
            perror("Не вдалося створити потік");
            return 1;
        }
    }

    // Очікуємо завершення всіх потоків
    for (int i = 0; i < num_threads; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Не вдалося приєднатися до потоку");
            return 1;
        }
    }

    // Знищуємо м'ютекс після завершення роботи всіх потоків
    pthread_mutex_destroy(&print_mutex);

    printf("Всі потоки завершили роботу.\n");
    return 0;
}
