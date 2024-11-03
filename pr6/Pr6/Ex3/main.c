#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* non_cancelable_thread(void *arg) {
    int iterations = *(int*)arg;
    int iteration = 0;

    // Встановлюємо режим, що забороняє скасування потоку
    if (pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL) != 0) {
        perror("Помилка встановлення стану потоку на несворотний");
        pthread_exit(NULL);
    }

    // Виконуємо цикл задану кількість ітерацій
    for (int i = 0; i < iterations; i++) {
        printf("Ітерація %d: Потік працює\n", iteration++);
        sleep(1); // Затримка на 1 секунду після кожного виведення
    }

    printf("Потік завершив всі ітерації звичайним чином.\n");
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

    int iterations = delay * 2; // Кількість ітерацій, рівна подвоєному часу затримки
    pthread_t thread;

    // Створюємо потік-нащадок
    if (pthread_create(&thread, NULL, non_cancelable_thread, &iterations) != 0) {
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
        printf("Потік завершено в результаті скасування (неочікувано).\n");
    } else {
        printf("Потік завершився звичайним чином.\n");
    }

    return 0;
}
