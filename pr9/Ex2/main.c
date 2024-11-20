#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

// Обробник сигналу SIGALRM
void alarm_handler(int sig) {
    if (sig == SIGALRM) {
        printf("Сигнал SIGALRM отримано. Виконую будильник.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Використання: %s <час у секундах> <повідомлення>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Перевірка та отримання інтервалу часу
    char *endptr;
    int seconds = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || seconds <= 0) {
        fprintf(stderr, "Помилка: час повинен бути додатнім цілим числом.\n");
        exit(EXIT_FAILURE);
    }

    // Отримання текстового повідомлення
    char *message = argv[2];
    if (strlen(message) == 0) {
        fprintf(stderr, "Помилка: текстове повідомлення не може бути порожнім.\n");
        exit(EXIT_FAILURE);
    }

    // Створення дочірнього процесу
    pid_t pid = fork();

    if (pid < 0) {
        perror("Не вдалося створити дочірній процес");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Дочірній процес
        // Встановлення обробника сигналу SIGALRM за допомогою sigaction
        struct sigaction sa;
        sa.sa_handler = alarm_handler;
        sa.sa_flags = 0; // Без додаткових опцій
        sigemptyset(&sa.sa_mask);

        if (sigaction(SIGALRM, &sa, NULL) == -1) {
            perror("Не вдалося встановити обробник для SIGALRM");
            exit(EXIT_FAILURE);
        }

        // Встановлюємо будильник
        alarm(seconds);

        // Очікуємо сигналу
        pause();

        // Виводимо повідомлення після сигналу
        printf("Будильник спрацював: %s\n", message);
        exit(EXIT_SUCCESS);
    } else {
        // Батьківський процес завершується
        printf("Будильник запущено у дочірньому процесі з PID: %d\n", pid);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
