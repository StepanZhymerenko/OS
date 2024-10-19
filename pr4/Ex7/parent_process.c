#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <number of throws per process> <number of processes> <number of experiments>\n", argv[0]);
        return 1;
    }

    int throws_per_process = atoi(argv[1]);
    int number_of_processes = atoi(argv[2]);
    int number_of_experiments = atoi(argv[3]);
    double total_pi_estimate = 0.0;

    for (int experiment = 0; experiment < number_of_experiments; experiment++) {
        int total_inside_circle = 0;

        for (int i = 0; i < number_of_processes; i++) {
            pid_t pid = fork();
            if (pid < 0) {
                perror("Fork failed");
                return 1;
            }

            if (pid == 0) {
                // Дочірній процес
                char throws_str[10];
                snprintf(throws_str, sizeof(throws_str), "%d", throws_per_process);
                execl("./monte_carlo", "monte_carlo", throws_str, NULL);
                perror("execl failed");
                exit(1);
            }
        }

        // Батьківський процес чекає на завершення всіх дочірніх процесів
        for (int i = 0; i < number_of_processes; i++) {
            int status;
            pid_t child_pid = wait(&status);

            // Отримуємо результат з коду повернення
            int count_inside_circle = WEXITSTATUS(status);
            total_inside_circle += count_inside_circle;
            printf("Child process (PID: %d) estimated %d points inside the circle.\n", child_pid, count_inside_circle);
        }

        // Обчислюємо загальну площу круга
        double pi_estimate = (4.0 * total_inside_circle) / (throws_per_process * number_of_processes);
        total_pi_estimate += pi_estimate;

        printf("Experiment %d: Estimated value of π: %f\n", experiment + 1, pi_estimate);
    }

    // Усереднюємо оцінки π
    double average_pi_estimate = total_pi_estimate / number_of_experiments;
    printf("Average estimated value of π over %d experiments: %f\n", number_of_experiments, average_pi_estimate);

    return 0;
}
