# Компілятор та флаги компіляції
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lm  # Додаємо бібліотеку math для лінкування

# Ціль за замовчуванням
all: program

# Створення виконуваного файлу
program: main.o taylor.o derivative.o
	$(CC) $(CFLAGS) -o program main.o taylor.o derivative.o $(LDFLAGS)

# Правило для компіляції main.c
main.o: main.c taylor.h derivative.h
	$(CC) $(CFLAGS) -c main.c -o main.o

# Правило для компіляції taylor.c
taylor.o: taylor.c taylor.h
	$(CC) $(CFLAGS) -c taylor.c -o taylor.o

# Правило для компіляції derivative.c
derivative.o: derivative.c derivative.h
	$(CC) $(CFLAGS) -c derivative.c -o derivative.o

# Очищення
clean:
	rm -f *.o program
