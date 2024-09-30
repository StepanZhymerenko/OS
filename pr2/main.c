#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "env_utils.h"

// Функція для запису змінної у файл
void save_variable_to_file(const char *var, const char *value) {
    FILE *file = fopen("env_vars.sh", "a");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for saving variables.\n");
        return;
    }
    // Записуємо команду для експорту змінної у файл
    fprintf(file, "export %s=\"%s\"\n", var, value);
    fclose(file);
}

// Функція для видалення змінної з файлу
void delete_variable_from_file(const char *var) {
    FILE *file = fopen("env_vars.sh", "a");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for deleting variable.\n");
        return;
    }
    // Записуємо команду для видалення змінної
    fprintf(file, "unset %s\n", var);
    fclose(file);
}

int main(int argc, char *argv[]) {
    int opt;
    const char *optstring = "hi:s:a:v:d:c";
    struct option longopts[] = {
        {"help",   no_argument,       0, 'h'},
        {"info",   required_argument, 0, 'i'},
        {"set",    required_argument, 0, 's'},
        {"assign", required_argument, 0, 'a'},
        {"value",  required_argument, 0, 'v'},
        {"del",    required_argument, 0, 'd'},
        {"clear",  no_argument,       0, 'c'},
        {0, 0, 0, 0}
    };

    char *assign_var_name = NULL;
    char *assign_value = NULL;

    if (argc == 1) {
        print_env();
        return 0;
    }

    while ((opt = getopt_long(argc, argv, optstring, longopts, NULL)) != -1) {
        switch (opt) {
            case 'h':
                print_help();
                return 0;
            case 'i':
                print_var_info(optarg);
                break;
            case 's': {
                set_var(optarg);
                // Розділяємо змінну та її значення і записуємо у файл
                char *var = strtok(strdup(optarg), "=");
                char *val = strtok(NULL, "=");
                if (var && val) {
                    save_variable_to_file(var, val);
                }
                break;
            }
            case 'a':
                assign_var_name = optarg;
                break;
            case 'v':
                assign_value = optarg;
                break;
            case 'd': {
                delete_var(optarg);
                // Записуємо команду видалення змінної у файл
                delete_variable_from_file(optarg);
                break;
            }
            case 'c': {
                clear_env();
                FILE *file = fopen("env_vars.sh", "a");
                if (file != NULL) {
                    fprintf(file, "unset $(compgen -e)\n");  // Видаляємо всі змінні
                    fclose(file);
                }
                break;
            }
            default:
                fprintf(stderr, "Unknown option. Use -h or --help for usage.\n");
                return 1;
        }
    }

    if (assign_var_name) {
        if (assign_value == NULL) {
            assign_value = "";
        }
        assign_var(assign_var_name, assign_value);
        save_variable_to_file(assign_var_name, assign_value);  // Зберегти змінну у файл
    }

    return 0;
}
