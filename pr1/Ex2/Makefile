# Компілятор та флаги компіляції
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lu  # Додаємо бібліотеку math для лінкування

# Ціль за замовчуванням
all: program

# Створення виконуваного файлу
program: main.o utils.o 
	$(CC) $(CFLAGS) -o program main.o utils.o $(LDFLAGS)

# Правило для компіляції main.c
main.o: main.c utils.h
	$(CC) $(CFLAGS) -c main.c -o main.o

# Правило для компіляції taylor.c
utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c -o utils.o

# Очищення
clean:
	rm -f *.o program
