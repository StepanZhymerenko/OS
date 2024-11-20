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
    struct sigaction sa;

    // Заповнення структури sigaction
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask); // Очищення маски блокування сигналів
    sa.sa_flags = 0;          // Без додаткових опцій

    // Встановлення обробників сигналів
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);

    // Відновлення стандартної поведінки для SIGPROF
    sa.sa_handler = SIG_DFL;
    sigaction(SIGPROF, &sa, NULL);

    // Ігнорування сигналу SIGHUP
    sa.sa_handler = SIG_IGN;
    sigaction(SIGHUP, &sa, NULL);

    printf("Програма запущена. PID: %d\n", getpid());

    // Нескінченний цикл очікування сигналів
    while (1) {
        pause(); // Очікування сигналу
    }

    return 0;
}
