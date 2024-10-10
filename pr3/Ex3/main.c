#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_HANDLERS 10 // Максимальна кількість обробників

void handler(int num) {
    sleep(1); // Затримка на 1 секунду
    printf("Обробник %d викликаний\n", num);
}

// Обгортка для виклику обробника з номером
void handler_wrapper(void) {
    static int current_handler = 0;
    current_handler++;
    handler(current_handler);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Використання: %s <кількість обробників>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int count = atoi(argv[1]); // Перетворення аргументу на число

    // Перевірка на максимальну кількість обробників
    if (count > MAX_HANDLERS) {
        fprintf(stderr, "Максимальна кількість обробників: %d\n", MAX_HANDLERS);
        return EXIT_FAILURE;
    }

    // Реєстрація обробників завершення процесу
    for (int i = 0; i < count; i++) {
        if (atexit(handler_wrapper) != 0) {
            fprintf(stderr, "Не вдалося зареєструвати обробник %d\n", i + 1);
            return EXIT_FAILURE;
        }
    }

    printf("Зареєстровано %d обробників завершення процесу.\n", count);

    // Завершення програми
    return EXIT_SUCCESS; // Викликає обробники перед завершенням
}
