# Компілятор та флаги компіляції
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -L./lib -Larraylist  # Додаємо бібліотеку math для лінкування

# Ціль за замовчуванням
all: program

# Створення виконуваного файлу
program: main.o arraylist.o 
	$(CC) $(CFLAGS) -o program main.o arraylist.o $(LDFLAGS)

# Правило для компіляції main.c
main.o: main.c arraylist.h
	$(CC) $(CFLAGS) -c main.c -o main.o

# Правило для компіляції taylor.c
arraylist.o: arraylist.c arraylist.h
	$(CC) $(CFLAGS) -c arraylist.c -o arraylist.o

# Очищення
clean:
	rm -f *.o program
