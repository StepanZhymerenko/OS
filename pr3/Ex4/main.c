#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>

#define DEFAULT_BUFFER_SIZE 127
#define MAX_BUFFER_SIZE 4096

void print_help() {
    printf("Довідка по програмі:\n");
    printf("Використання: ./prog [-b <розмір_буфера>] [-h|--help]\n");
    printf(" -h, --help    Вивести цю довідку\n");
    printf(" -b <size>     Вказати розмір буфера для команди (за замовчуванням 127)\n");
}

void clear_screen() {
    system("clear");
}

int main(int argc, char *argv[]) {
    int buffer_size = DEFAULT_BUFFER_SIZE; // Значення за замовчуванням
    char command[MAX_BUFFER_SIZE];
    char username[256];

    // Обробка аргументів командного рядка
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help();
            return EXIT_SUCCESS;
        } else if (strcmp(argv[i], "-b") == 0 && i + 1 < argc) {
            buffer_size = atoi(argv[++i]); // Встановлюємо розмір буфера
            if (buffer_size <= 0 || buffer_size > MAX_BUFFER_SIZE) {
                fprintf(stderr, "Неправильний розмір буфера. Використовується розмір за замовчуванням (%d).\n", DEFAULT_BUFFER_SIZE);
                buffer_size = DEFAULT_BUFFER_SIZE;
            }
        } else if (strcmp(argv[i], "-b") == 0) {
            fprintf(stderr, "Вкажіть розмір буфера після -b.\n");
            return EXIT_FAILURE;
        }
    }

    // Отримання імені користувача
    struct passwd *pw = getpwuid(getuid());
    if (pw != NULL) {
        strcpy(username, pw->pw_name);
    } else {
        strcpy(username, "невідомий користувач");
    }

    printf("Ви працюєте з командним процесором: %s\n", username);

    while (1) {
        // Запрошення для введення команди
        printf("[%s]$ ", username);
        if (fgets(command, buffer_size, stdin) == NULL) {
            perror("Помилка при читанні команди");
            break;
        }

        // Видалення символу нового рядка
        command[strcspn(command, "\n")] = 0;

        // Команда для завершення роботи
        if (strcmp(command, "stop") == 0) {
            break;
        }

        // Виконання команди
        int status = system(command);
        if (status == -1) {
            printf("Не вдалося виконати команду: %s\n", command);
        }
    }

    // Повідомлення перед завершенням
    printf("Wait 3 seconds...\n");
    sleep(3);
    clear_screen();
    
    return EXIT_SUCCESS;
}
