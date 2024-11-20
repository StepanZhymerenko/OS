#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define MAX_ITERATIONS 10 // Максимальна кількість ітерацій

// Глобальні змінні
pid_t child_pid = 0;
pid_t parent_pid = 0;
volatile sig_atomic_t signal_received = 0;
volatile sig_atomic_t iterations = 0; // Лічильник ітерацій
volatile sig_atomic_t stop_program = 0; // Прапорець завершення програми

// Обробник сигналів
void signal_handler(int sig) {
    if (sig == SIGUSR1) {
        signal_received = 1; // Встановлюємо прапорець для сигналу
    } else if (sig == SIGTERM) {
        stop_program = 1; // Встановлюємо прапорець завершення
    }
}

// Очікування сигналу з перевіркою завершення
void wait_for_signal() {
    while (!signal_received && !stop_program) {
        pause(); // Очікуємо сигналу
    }
    signal_received = 0; // Скидаємо прапорець
}

int main() {
    // Зберігаємо PID батьківського процесу
    parent_pid = getpid();

    // Встановлення обробника сигналів
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Не вдалося встановити обробник для SIGUSR1");
        exit(EXIT_FAILURE);
    }

    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("Не вдалося встановити обробник для SIGTERM");
        exit(EXIT_FAILURE);
    }

    // Створення дочірнього процесу
    child_pid = fork();

    if (child_pid < 0) {
        perror("Не вдалося створити дочірній процес");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Дочірній процес
        printf("Дочірній процес запущено. PID: %d\n", getpid());
        // Надсилаємо перший сигнал батьківському процесу
        kill(parent_pid, SIGUSR1);

        while (!stop_program && iterations < MAX_ITERATIONS) {
            wait_for_signal(); // Очікуємо сигналу
            if (stop_program) break; // Перевірка завершення
            printf("Дочірній процес: Моя черга! Ітерація %d\n", iterations + 1);
            iterations++;
            kill(parent_pid, SIGUSR1); // Надсилаємо сигнал батьківському процесу
        }
    } else {
        // Батьківський процес
        printf("Батьківський процес запущено. PID: %d\n", getpid());

        while (!stop_program && iterations < MAX_ITERATIONS) {
            wait_for_signal(); // Очікуємо сигналу
            if (stop_program) break; // Перевірка завершення
            printf("Батьківський процес: Моя черга! Ітерація %d\n", iterations + 1);
            iterations++;
            kill(child_pid, SIGUSR1); // Надсилаємо сигнал дочірньому процесу
        }
    }

    // Завершення програми
    if (child_pid > 0) {
        printf("Батьківський процес завершено.\n");
    } else {
        printf("Дочірній процес завершено.\n");
    }

    return 0;
}
