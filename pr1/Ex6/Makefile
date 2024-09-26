# Компілятор та флаги компіляції
CC = gcc
CFLAGS = -Wall -g

# Ціль за замовчуванням
all: program

# Створення виконуваного файлу
program: main.o matrix.o
	$(CC) $(CFLAGS) -o program main.o matrix.o

# Правило для компіляції main.c
main.o: main.c matrix.h
	$(CC) $(CFLAGS) -c main.c -o main.o

# Правило для компіляції matrix.c
matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c -o matrix.o

# Очищення
clean:
	rm -f *.o program
