#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Спрощений аналог функції system()
int my_system(const char *command) {
    pid_t pid;
    int status;

    // Створюємо процес за допомогою fork()
    pid = fork();

    if (pid < 0) {
        // Помилка при виклику fork
        perror("fork failed");
        return -1;
    } else if (pid == 0) {
        // Дочірній процес
        execl("/bin/sh", "sh", "-c", command, (char *)NULL);  // Виконуємо команду через shell
        // Якщо exec не спрацює, виводимо помилку і виходимо
        perror("execl failed");
        exit(EXIT_FAILURE);
    } else {
        // Батьківський процес
        // Очікуємо завершення дочірнього процесу
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid failed");
            return -1;
        }

        // Повертаємо статус завершення дочірнього процесу
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);  // Код повернення дочірнього процесу
        } else {
            return -1;  // Процес завершився не коректно
        }
    }
}

int main() {
    // Тестування функції my_system
    printf("Executing 'ls -l':\n");
    int ret = my_system("ls -l");
    
    if (ret != -1) {
        printf("'ls -l' executed with return code: %d\n", ret);
    } else {
        printf("Error during execution\n");
    }

    return 0;
}
