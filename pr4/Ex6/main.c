#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork(); // Створюємо процес-нащадок

    if (pid < 0) {
        // Помилка при виклику fork
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Процес-нащадок
        printf("Child process (PID: %d) is exiting...\n", getpid());
        exit(0); // Завершення процесу-нащадка
    } else {
        // Батьківський процес
        printf("Parent process (PID: %d), child process (PID: %d) created\n", getpid(), pid);
        
        // Викликаємо команду ps для показу процесу-зомбі
        printf("Running 'ps' to show the child as a zombie:\n");
        system("ps -l");

        // Затримка для того, щоб дати час процесу перейти в стан зомбі
        sleep(10);

        // Викликаємо wait для видалення процесу-зомбі
        wait(NULL);
        printf("Child process (PID: %d) is now removed after wait.\n", pid);

        // Викликаємо команду ps для показу, що процесу-зомбі більше немає
        printf("Running 'ps' again after wait:\n");
        system("ps -l");
    }

    return 0;
}
