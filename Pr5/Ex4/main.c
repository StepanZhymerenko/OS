#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Функція для обчислення факторіалу
unsigned long long factorial(int n) {
    if (n == 0) return 1;
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Перевірка на просте число
int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

// 1. Повернення через глобальні змінні
unsigned long long global_catalan_numbers[10];
int global_prime_numbers[10];

// Функція для обчислення чисел Каталана через глобальні змінні
void* calculate_catalan_global(void* arg) {
    int n = *((int*)arg);
    for (int i = 0; i < n; i++) {
        global_catalan_numbers[i] = factorial(2 * i) / (factorial(i + 1) * factorial(i));
    }
    return NULL;
}

// Функція для обчислення простих чисел через глобальні змінні
void* calculate_primes_global(void* arg) {
    int n = *((int*)arg);
    int count = 0;
    int num = 2;
    while (count < n) {
        if (is_prime(num)) {
            global_prime_numbers[count] = num;
            count++;
        }
        num++;
    }
    return NULL;
}

// 2. Повернення через змінну, яка повертається потоком
void* calculate_catalan_return(void* arg) {
    int n = *((int*)arg);
    unsigned long long* catalan_numbers = malloc(n * sizeof(unsigned long long));
    for (int i = 0; i < n; i++) {
        catalan_numbers[i] = factorial(2 * i) / (factorial(i + 1) * factorial(i));
    }
    return (void*)catalan_numbers;
}

// 3. Повернення через аргумент за допомогою указівника
void* calculate_primes_arg(void* arg) {
    int* prime_numbers = (int*)arg;
    int count = 0;
    int num = 2;
    while (count < 10) {  // Обчислюємо 10 простих чисел
        if (is_prime(num)) {
            prime_numbers[count] = num;
            count++;
        }
        num++;
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3, thread4;
    int count = 10; // Кількість чисел для обчислення

    // 1. Використання глобальних змінних
    if (pthread_create(&thread1, NULL, calculate_catalan_global, &count) != 0) {
        perror("Failed to create thread for Catalan numbers (global)");
        return 1;
    }

    if (pthread_create(&thread2, NULL, calculate_primes_global, &count) != 0) {
        perror("Failed to create thread for prime numbers (global)");
        return 1;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Global Catalan numbers: ");
    for (int i = 0; i < count; i++) {
        printf("%llu ", global_catalan_numbers[i]);
    }
    printf("\n");

    printf("Global Prime numbers: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", global_prime_numbers[i]);
    }
    printf("\n");

    // 2. Використання повернення значення з потоку
    unsigned long long* returned_catalan_numbers;
    if (pthread_create(&thread3, NULL, calculate_catalan_return, &count) != 0) {
        perror("Failed to create thread for Catalan numbers (return)");
        return 1;
    }

    pthread_join(thread3, (void**)&returned_catalan_numbers);

    printf("Returned Catalan numbers: ");
    for (int i = 0; i < count; i++) {
        printf("%llu ", returned_catalan_numbers[i]);
    }
    printf("\n");

    free(returned_catalan_numbers); // Очищення виділеної пам'яті

    // 3. Використання аргументу для передачі результатів
    int arg_prime_numbers[10];  // Місце для результатів
    if (pthread_create(&thread4, NULL, calculate_primes_arg, arg_prime_numbers) != 0) {
        perror("Failed to create thread for prime numbers (argument)");
        return 1;
    }

    pthread_join(thread4, NULL);

    printf("Arg Prime numbers: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arg_prime_numbers[i]);
    }
    printf("\n");

    return 0;
}
