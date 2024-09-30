#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "env_utils.h"

// Змінна для зберігання оточення
extern char **environ;

// Функція для виведення допомоги
void print_help() {
    printf("Usage: environ [options]\n");
    printf("Options:\n");
    printf("  -h, --help               Show help message\n");
    printf("  -i, --info <var>         Show the value of the specified environment variable\n");
    printf("  -s, --set <var=value>    Set the environment variable to the given value\n");
    printf("  -a, --assign <var> -v, --value <value>  Assign the environment variable\n");
    printf("  -d, --del <var>          Delete the specified environment variable\n");
    printf("  -c, --clear              Clear all environment variables\n");
}

// Функція для виведення всіх змінних оточення
void print_env() {
    char **env = environ;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
}

// Функція для виведення змінної оточення
void print_var_info(const char *var) {
    char *value = getenv(var);
    if (value) {
        printf("%s=%s\n", var, value);
    } else {
        printf("Variable '%s' not found in the environment.\n", var);
    }
}

// Функція для встановлення значення змінної оточення
void set_var(const char *assignment) {
    char *equal_sign = strchr(assignment, '=');
    if (equal_sign) {
        char *var = strndup(assignment, equal_sign - assignment);
        char *value = equal_sign + 1;
        setenv(var, value, 1);
        printf("Set: %s=%s\n", var, getenv(var));
        free(var);
    } else {
        printf("Invalid format. Use var=value.\n");
    }
}

// Функція для встановлення змінної через -a та -v
void assign_var(const char *var, const char *value) {
    if (var) {
        if (!value) {
            value = "";  // Якщо значення не вказано, встановлюємо порожній рядок
        }
        setenv(var, value, 1);
        printf("Assigned: %s=%s\n", var, getenv(var));
    } else {
        fprintf(stderr, "Error: Variable name not specified.\n");
    }
}

// Функція для видалення змінної оточення
void delete_var(const char *var) {
    if (unsetenv(var) == 0) {
        printf("Deleted: %s\n", var);
    } else {
        printf("Error: Could not delete variable '%s'.\n", var);
    }
}

// Функція для очищення всього оточення
void clear_env() {
    clearenv();
    printf("Environment cleared.\n");
}
