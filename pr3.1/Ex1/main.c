#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;

    // 1. Запуск нового процесу на передньому плані
    printf("Запуск нового процесу на передньому плані...\n");
    pid1 = fork();

    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // Дочірній процес
        printf("Це дочірній процес 1 з PID: %d. Виконую команду `sleep 10`\n", getpid());
        execlp("sleep", "sleep", "10", (char *)NULL);
        exit(EXIT_SUCCESS);
    } else {
        // Батьківський процес
        sleep(2); // Дати час дочірньому процесу на виконання
        printf("Дочірній процес 1 запущений. PID: %d\n", pid1);
    }

    // 2. Запуск нового процесу у фоновому режимі
    printf("Запуск нового процесу у фоновому режимі...\n");
    pid2 = fork();

    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Дочірній процес
        printf("Це дочірній процес 2 з PID: %d. Виконую команду `sleep 5`\n", getpid());
        execlp("sleep", "sleep", "5", (char *)NULL);
        exit(EXIT_SUCCESS);
    } else {
        // Батьківський процес
        printf("Дочірній процес 2 запущений у фоновому режимі. PID: %d\n", pid2);
    }

    // 3. Призупинення обох процесів
    sleep(2);
    printf("Призупиняю обидва дочірні процеси...\n");
    kill(pid1, SIGSTOP);
    kill(pid2, SIGSTOP);

    // 4. Відновлення обох процесів
    sleep(2);
    printf("Відновлюю обидва дочірні процеси...\n");
    kill(pid1, SIGCONT);
    kill(pid2, SIGCONT);

    // 5. Зміна між режимами (фоновий і передній план)
    sleep(2);
    printf("Переводжу процес 1 (PID: %d) у фоновий режим...\n", pid1);
    if (setpgid(pid1, pid1) == 0) {
        printf("Процес 1 успішно переведено у фоновий режим.\n");
    }

    sleep(2);
    printf("Переводжу процес 1 назад у передній план...\n");
    kill(pid1, SIGCONT);  // Відновлюємо процес 1 у передньому плані

    // Завершення дочірніх процесів
    waitpid(pid1, NULL, 0);  // Очікуємо завершення процесу 1
    printf("Дочірній процес 1 завершений\n");
    waitpid(pid2, NULL, 0);  // Очікуємо завершення процесу 2
    printf("Дочірній процес 2 завершений\n");

    // Демонстрація команд ps, top
    printf("\nЗапускаю команду `ps` для перегляду процесів:\n");
    system("ps");

    printf("\nЗапускаю команду `top` (натисніть q для виходу):\n");
    system("top -b -n 1");  // -b для фонової роботи, -n 1 для одного циклу

    // Завершення процесу (як приклад)
    printf("\nЗапускаю команду `kill %d` (вбити процес за PID):\n", pid1);
    kill(pid1, SIGKILL);  // Завершення процесу 1

    return 0;
}
