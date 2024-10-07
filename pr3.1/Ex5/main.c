#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <pwd.h>

#define DEFAULT_FILE_NAME "default_file"
#define MAX_NUMBER 100

void create_child_program(int child_number) {
    char *file_name = getenv("FILE_NAME");
    char complete_file_name[256];

    if (file_name == NULL) {
        file_name = DEFAULT_FILE_NAME;
    }

    snprintf(complete_file_name, sizeof(complete_file_name), "%s_%d.txt", file_name, child_number);

    FILE *file = fopen(complete_file_name, "w");
    if (file == NULL) {
        perror("Не вдалося відкрити файл");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < child_number; i++) {
        double random_number = (double)rand() / RAND_MAX;
        fprintf(file, "%f\n", random_number);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    char *file_name = NULL;
    int number_of_children = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
            if (i + 1 < argc) {
                file_name = argv[++i];
                setenv("FILE_NAME", file_name, 1);
            } else {
                fprintf(stderr, "Опція -f вимагає аргумент.\n");
                return EXIT_FAILURE;
            }
        } else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--number") == 0) {
            if (i + 1 < argc) {
                number_of_children = atoi(argv[++i]);
                if (number_of_children <= 0 || number_of_children > MAX_NUMBER) {
                    fprintf(stderr, "Кількість дочірніх програм має бути більше 0 і менше або дорівнює %d.\n", MAX_NUMBER);
                    return EXIT_FAILURE;
                }
            } else {
                fprintf(stderr, "Опція -n вимагає аргумент.\n");
                return EXIT_FAILURE;
            }
        }
    }

    for (int i = 1; i <= number_of_children; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            create_child_program(i);
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < number_of_children; i++) {
        wait(NULL);
    }

    return EXIT_SUCCESS;
}
