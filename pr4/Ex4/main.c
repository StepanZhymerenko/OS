#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>  
#include <sys/types.h>
#include <sys/wait.h>

// Функція для пошуку виконуваного файлу у каталогах змінної PATH
char *find_executable(const char *file) {
    char *path = getenv("PATH");  // Отримуємо змінну PATH
    if (path == NULL) {
        return NULL;
    }

    // Копіюємо змінну PATH, оскільки strtok змінює рядок
    char *path_copy = strdup(path);
    char *dir = strtok(path_copy, ":");  // Поділяємо PATH на каталоги
    
    static char full_path[1024];  // Буфер для повного шляху

    // Перебираємо кожен каталог у PATH
    while (dir != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, file);
        if (access(full_path, X_OK) == 0) {  // Перевіряємо, чи файл виконуваний
            free(path_copy);  // Звільняємо пам'ять після використання
            return full_path;  // Повертаємо знайдений шлях
        }
        dir = strtok(NULL, ":");  // Переходимо до наступного каталогу
    }

    free(path_copy);
    return NULL;  // Якщо файл не знайдено
}

// Еквівалент execvp, але використовує execv
int my_execvp(const char *file, char *const argv[]) {
    // Знайдемо виконуваний файл у змінній PATH
    char *exec_path = find_executable(file);
    if (exec_path == NULL) {
        fprintf(stderr, "Error: command not found: %s\n", file);
        return -1;
    }

    // Викликаємо execv з повним шляхом до виконуваного файлу
    return execv(exec_path, argv);
}

// Еквівалент execlp, але використовує execl
int my_execlp(const char *file, const char *arg, ...) {
    // Створюємо список аргументів (як змінний список аргументів)
    va_list args;
    va_start(args, arg);

    // Порахуємо кількість аргументів
    const char *current_arg = arg;
    char *argv[1024];  // Масив для аргументів
    int argc = 0;

    while (current_arg != NULL) {
        argv[argc++] = (char *)current_arg;
        current_arg = va_arg(args, char *);  // Оголошуємо аргумент як char *
    }
    argv[argc] = NULL;  // Останній елемент має бути NULL

    va_end(args);

    // Використовуємо my_execvp для виконання команди
    return my_execvp(file, argv);
}

int main() {
    // Тестування my_execvp
    char *args[] = {"ls", "-l", NULL};
    if (fork() == 0) {
        my_execvp("ls", args);
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);  // Очікуємо завершення дочірнього процесу
    }

    // Тестування my_execlp
    if (fork() == 0) {
        my_execlp("ls", "ls", "-a", NULL);
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);  // Очікуємо завершення дочірнього процесу
    }

    return 0;
}
