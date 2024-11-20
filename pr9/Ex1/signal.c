#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Функція для обробки сигналів
void signal_handler(int signal_number) {
    switch (signal_number) {
        case SIGINT:
            printf("Сигнал SIGINT отримано. Продовжую роботу.\n");
            break;
        case SIGTERM:
            printf("Сигнал SIGTERM отримано. Завершую програму.\n");
            exit(0);
        case SIGUSR1:
            printf("Сигнал SIGUSR1 отримано. Завершую програму.\n");
            exit(0);
        default:
            break;
    }
}

int main() {
    // Встановлення обробників сигналів
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        perror("Не вдалося встановити обробник для SIGINT");
        exit(1);
    }

    if (signal(SIGTERM, signal_handler) == SIG_ERR) {
        perror("Не вдалося встановити обробник для SIGTERM");
        exit(1);
    }

    if (signal(SIGUSR1, signal_handler) == SIG_ERR) {
        perror("Не вдалося встановити обробник для SIGUSR1");
        exit(1);
    }

    if (signal(SIGPROF, SIG_DFL) == SIG_ERR) {
        perror("Не вдалося відновити стандартну поведінку для SIGPROF");
        exit(1);
    }

    if (signal(SIGHUP, SIG_IGN) == SIG_ERR) {
        perror("Не вдалося ігнорувати SIGHUP");
        exit(1);
    }

    printf("Програма запущена. PID: %d\n", getpid());

    // Нескінченний цикл очікування сигналів
    while (1) {
        pause(); // Очікування сигналу
    }

    return 0;
}
