#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Глобальні змінні для передачі інформації
pid_t child_pid = 0;
pid_t parent_pid = 0;

// Обробник сигналу реального часу
void realtime_signal_handler(int sig, siginfo_t *info, void *context) {
    printf("Дочірній процес отримав сигнал %d (%s) з додатковою інформацією: %d\n",
           sig, strsignal(sig), info->si_value.sival_int);
}

// Обробник сигналу завершення
void termination_signal_handler(int sig) {
    printf("Дочірній процес завершується через сигнал %d (%s).\n", sig, strsignal(sig));
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Використання: %s <кількість повідомлень>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int message_count = atoi(argv[1]);
    if (message_count <= 0) {
        fprintf(stderr, "Помилка: кількість повідомлень повинна бути додатнім числом.\n");
        exit(EXIT_FAILURE);
    }

    // Зберігаємо PID батьківського процесу
    parent_pid = getpid();

    // Створення дочірнього процесу
    child_pid = fork();

    if (child_pid < 0) {
        perror("Не вдалося створити дочірній процес");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Дочірній процес
        printf("Дочірній процес запущено. PID: %d\n", getpid());

        // Встановлення обробників сигналів
        struct sigaction sa_rt, sa_term;

        // Для сигналів реального часу
        sa_rt.sa_sigaction = realtime_signal_handler;
        sa_rt.sa_flags = SA_SIGINFO; // Для отримання додаткової інформації
        sigemptyset(&sa_rt.sa_mask);

        if (sigaction(SIGRTMIN, &sa_rt, NULL) == -1) {
            perror("Не вдалося встановити обробник для сигналу реального часу");
            exit(EXIT_FAILURE);
        }

        // Для сигналу завершення
        sa_term.sa_handler = termination_signal_handler;
        sa_term.sa_flags = 0;
        sigemptyset(&sa_term.sa_mask);

        if (sigaction(SIGTERM, &sa_term, NULL) == -1) {
            perror("Не вдалося встановити обробник для SIGTERM");
            exit(EXIT_FAILURE);
        }

        // Дочірній процес очікує сигналів
        while (1) {
            pause();
        }
    } else {
        // Батьківський процес
        printf("Батьківський процес запущено. PID: %d\n", getpid());

        // Надсилання сигналів з додатковою інформацією
        for (int i = 1; i <= message_count; i++) {
            union sigval value;
            value.sival_int = i; // Номер виклику
            if (sigqueue(child_pid, SIGRTMIN, value) == -1) {
                perror("Не вдалося надіслати сигнал");
                exit(EXIT_FAILURE);
            }
            printf("Батьківський процес надіслав сигнал %d з додатковою інформацією: %d\n", SIGRTMIN, i);
            sleep(1); // Пауза між сигналами
        }

        // Надсилання сигналу завершення
        printf("Батьківський процес надсилає сигнал завершення (SIGTERM).\n");
        kill(child_pid, SIGTERM);

        // Очікування завершення дочірнього процесу
        wait(NULL);
        printf("Батьківський процес завершено.\n");
    }

    return 0;
}
