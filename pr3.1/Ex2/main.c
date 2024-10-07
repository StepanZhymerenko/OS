#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1024

int main(int argc, char *argv[]) {
    // Перевірка кількості аргументів
    if (argc < 2) {
        fprintf(stderr, "Використання: %s \"команда1; команда2; ...\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Обчислення необхідної довжини для об'єднання всіх аргументів
    size_t total_length = 0;
    for (int i = 1; i < argc; i++) {
        total_length += strlen(argv[i]) + 1; // Додаємо 1 для пробілу або кінця рядка
    }

    // Перевірка на максимальну довжину
    if (total_length >= MAX_COMMAND_LENGTH) {
        fprintf(stderr, "Помилка: команда перевищує максимальну довжину %d символів\n", MAX_COMMAND_LENGTH);
        return EXIT_FAILURE;
    }

    // Зберігання команди
    char command[MAX_COMMAND_LENGTH] = "";

    // Об'єднання всіх аргументів в одну строку
    for (int i = 1; i < argc; i++) {
        strcat(command, argv[i]);
        if (i < argc - 1) {
            strcat(command, " "); // Додаємо пробіл між аргументами
        }
    }

    // Виконання команди
    int return_code = system(command);

    // Вивід коду завершення
    if (return_code == -1) {
        perror("system");
        return EXIT_FAILURE;
    } else {
        printf("Код завершення: %d\n", WEXITSTATUS(return_code));
    }

    return EXIT_SUCCESS;
}
