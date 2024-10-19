#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

// Функція для виведення інформації про процес
void print_process_info(int show_pid, int show_ppid, int show_gid, int show_uid) {
    if (show_pid) {
        printf("Process ID (PID): %d\n", getpid());
    }
    if (show_ppid) {
        printf("Parent Process ID (PPID): %d\n", getppid());
    }
    if (show_gid) {
        printf("Group ID (GID): %d\n", getgid());
    }
    if (show_uid) {
        printf("User ID (UID): %d\n", getuid());
    }
}

int main(int argc, char *argv[]) {
    // Перевірка, які аргументи передано
    int show_pid = 0, show_ppid = 0, show_gid = 0, show_uid = 0;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--pid") == 0) {
            show_pid = 1;
        }
        if (strcmp(argv[i], "--ppid") == 0) {
            show_ppid = 1;
        }
        if (strcmp(argv[i], "--gid") == 0) {
            show_gid = 1;
        }
        if (strcmp(argv[i], "--uid") == 0) {
            show_uid = 1;
        }
    }
    
    // Виклик функції для виведення інформації про процес
    print_process_info(show_pid, show_ppid, show_gid, show_uid);
    
    return 0;
}
