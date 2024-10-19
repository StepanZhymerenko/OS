#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#define RADIUS 1.0

// Функція для генерації випадкових чисел
double random_double() {
    return (double)rand() / (double)RAND_MAX;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number of throws>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]); // Кількість "кидків"
    int count_inside_circle = 0;

    // Ініціалізація генератора випадкових чисел
    srand(time(NULL) ^ (getpid() << 16)); // Змішуємо час з PID для уникнення конфліктів

    // Генерація точок і підрахунок, скільки з них потрапили в круг
    for (int i = 0; i < n; i++) {
        double x = random_double() * 2 * RADIUS - RADIUS; // x в межах [-RADIUS, RADIUS]
        double y = random_double() * 2 * RADIUS - RADIUS; // y в межах [-RADIUS, RADIUS]
        
        if (x * x + y * y <= RADIUS * RADIUS) {
            count_inside_circle++;
        }
    }

    // Повертаємо кількість точок, що потрапили в круг через код повернення
    return count_inside_circle; // Повертаємо значення безпосередньо
}
