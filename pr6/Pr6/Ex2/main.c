#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* print_thread(void *arg) {
    int iteration = 0;

    // Встановлюємо режим асинхронного скасування
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    // Нескінченний цикл з виведенням інформації
    while (1) {
        printf("Ітерація %d: Потік працює\n", iteration++);
        sleep(1); // Затримка на 1 секунду
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Використання: %s <час_затримки>\n", argv[0]);
        return 1;
    }

    int delay = atoi(argv[1]);
    pthread_t thread;

    // Створюємо потік-нащадок
    if (pthread_create(&thread, NULL, print_thread, NULL) != 0) {
        perror("Не вдалося створити потік");
        return 1;
    }

    // Засинаємо на задану кількість секунд
    sleep(delay);

    // Скасовуємо потік
    printf("Спроба скасувати потік...\n");
    if (pthread_cancel(thread) != 0) {
        perror("Не вдалося скасувати потік");
        return 1;
    }

    // Очікуємо завершення потоку
    void *res;
    if (pthread_join(thread, &res) != 0) {
        perror("Не вдалося приєднатися до потоку");
        return 1;
    }

    // Аналізуємо статус завершення потоку
    if (res == PTHREAD_CANCELED) {
        printf("Потік завершено в результаті скасування.\n");
    } else {
        printf("Потік завершився звичайним чином.\n");
    }

    return 0;
}
