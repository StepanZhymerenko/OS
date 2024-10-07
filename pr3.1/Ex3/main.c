#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_HANDLERS 10 // Максимальна кількість обробників

int handler_num[MAX_HANDLERS]; // Масив для зберігання номерів обробників
int handler_count = 0; // Змінна для зберігання кількості обробників

void handler() {
    // Виводимо номер обробника
    for (int i = 0; i < handler_count; i++) {
        sleep(1); // Затримка на 1 секунду
        printf("Обробник %d викликаний\n", handler_num[i]);
    }
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
        handler_num[i] = i + 1; // Зберігаємо номер обробника в масив
        handler_count++;
    }

    // Реєстрація єдиного обробника завершення процесу
    if (atexit(handler) != 0) {
        fprintf(stderr, "Не вдалося зареєструвати обробник\n");
        return EXIT_FAILURE;
    }

    printf("Зареєстровано %d обробників завершення процесу.\n", count);
    
    // Завершення програми
    return EXIT_SUCCESS; // Викликає обробники перед завершенням
}
