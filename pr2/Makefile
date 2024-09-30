# Компілятор та флаги компіляції
CC = gcc
CFLAGS = -Wall -g

# Ціль за замовчуванням
all: program

# Створення виконуваного файлу з лінкуванням бібліотеки math (-lm)
program: main.o env_utils.o
	$(CC) $(CFLAGS) -o program main.o env_utils.o -lm

# Правило для компіляції main.c
main.o: main.c env_utils.c 
	$(CC) $(CFLAGS) -c main.c -o main.o

# Правило для компіляції env_utils.c
env_utils.o: env_utils.c env_utils.h
	$(CC) $(CFLAGS) -c env_utils.c -o env_utils.o
 
#

# Очищення
clean:
	rm -f *.o program
