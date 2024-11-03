#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 10000000 // Кількість доданків для обчислення π

void* calculate_pi(void *arg) {
    int i;
    double pi = 0.0;
    int sign = 1;

    // Встановлюємо режим синхронного скасування
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    for (i = 0; i < N; i++) {
        // Початок секції, що не скасовується
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

        // Додаємо черговий член ряду
        pi += sign * (1.0 / (2 * i + 1));
        sign = -sign;

        // Кінець секції, що не скасовується
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

        // Формування точки виходу для скасування
        pthread_testcancel();

        // Виводимо поточне значення π кожні 10000 ітерацій
        if (i % 10000 == 0) {
            printf("Поточне значення π: %.15f\n", pi * 4);
        }

        // Додаємо затримку для уповільнення обчислення
        usleep(100); // Затримка на 100 мікросекунд
    }

    // Множимо результат на 4 для отримання остаточного значення π
    pi *= 4;
    printf("Розрахунки завершено. Обчислене значення π: %.15f\n", pi);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Використання: %s <час_затримки>\n", argv[0]);
        return 1;
    }

    int delay = atoi(argv[1]);
    if (delay <= 0) {
        fprintf(stderr, "Час затримки має бути додатнім числом.\n");
        return 1;
    }

    pthread_t thread;

    // Створюємо потік-нащадок для обчислення π
    if (pthread_create(&thread, NULL, calculate_pi, NULL) != 0) {
        perror("Не вдалося створити потік");
        return 1;
    }

    // Засинаємо на задану кількість секунд
    sleep(delay);

    // Спроба скасувати потік
    printf("Спроба скасувати потік...\n");
    if (pthread_cancel(thread) != 0) {
        perror("Не вдалося скасувати потік");
    }

    // Очікуємо завершення потоку
    void *res;
    if (pthread_join(thread, &res) != 0) {
        perror("Не вдалося приєднатися до потоку");
        return 1;
    }

    // Аналізуємо статус завершення потоку
    if (res == PTHREAD_CANCELED) {
        printf("Потік було скасовано.\n");
    } else {
        printf("Потік завершився звичайним чином.\n");
    }

    return 0;
}
