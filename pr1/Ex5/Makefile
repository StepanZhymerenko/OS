# Компілятор та флаги компіляції
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lm  # Додаємо бібліотеку math для лінкування

# Ціль за замовчуванням
all: program

# Створення виконуваного файлу
program: main.o linkedlist.o 
	$(CC) $(CFLAGS) -o program main.o linkedlist.o $(LDFLAGS)

# Правило для компіляції main.c
main.o: main.c linkedlist.h 
	$(CC) $(CFLAGS) -c main.c -o main.o

# Правило для компіляції taylor.c
linkedlist.o: linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) -c linkedlist.c -o linkedlist.o


# Очищення
clean:
	rm -f *.o program
