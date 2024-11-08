#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

double epsilon = 1e-6;  // Задана точність
double a = 0.0;         // Нижня межа інтегрування
double b = 2.0;         // Верхня межа інтегрування
int p = 4;              // Кількість потоків (за замовчуванням)
double result = 0.0;    // Змінна для збереження результату
pthread_mutex_t mutex;  // М'ютекс для синхронізації доступу до змінної result

// Функція для інтегрування
double f(double x) {
    return 4 - x * x;
}

// Функція для обчислення часткового інтегралу на інтервалі [a_i, b_i] з точністю epsilon
double integrate_section(double a_i, double b_i, double epsilon) {
    int n = 1;
    double h = (b_i - a_i) / n;
    double integral_n = h * f(a_i + h / 2);
    
    while (1) {
        n *= 2;
        h = (b_i - a_i) / n;
        double integral_2n = 0.0;
        
        for (int i = 0; i < n; i++) {
            integral_2n += f(a_i + (i + 0.5) * h);
        }
        
        integral_2n *= h;
        
        if (fabs(integral_2n - integral_n) < epsilon) {
            return integral_2n;
        }
        
        integral_n = integral_2n;
    }
}

// Функція потоку для обчислення часткового інтегралу
void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    double h = (b - a) / p;
    double a_i = a + thread_id * h;
    double b_i = a_i + h;
    
    double partial_result = integrate_section(a_i, b_i, epsilon);
    
    // Захист оновлення загального результату за допомогою м'ютекса
    pthread_mutex_lock(&mutex);
    result += partial_result;
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

int main(int argc, char* argv[]) {
    // Ініціалізація м'ютекса
    pthread_mutex_init(&mutex, NULL);
    
    // Обробка параметрів командного рядка
    if (argc > 1) {
        p = atoi(argv[1]);
    }
    
    printf("Кількість потоків: %d\n", p);
    printf("Інтегрування від %f до %f з точністю %f\n", a, b, epsilon);
    
    pthread_t threads[p];
    int thread_ids[p];
    
    // Створення потоків
    for (int i = 0; i < p; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }
    
    // Очікування завершення роботи потоків
    for (int i = 0; i < p; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Результат обчислення інтегралу: %.5f\n", result);
    
    // Знищення м'ютекса
    pthread_mutex_destroy(&mutex);
    
    return 0;
}
