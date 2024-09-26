# Компілятор та флаги компіляції
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -L./lib -Lstudents  # Додаємо бібліотеку math для лінкування

# Ціль за замовчуванням
all: program

# Створення виконуваного файлу
program: main.o student.o 
	$(CC) $(CFLAGS) -o program main.o student.o $(LDFLAGS)

# Правило для компіляції main.c
main.o: main.c student.h
	$(CC) $(CFLAGS) -c main.c -o main.o

# Правило для компіляції taylor.c
student.o: student.c student.h
	$(CC) $(CFLAGS) -c student.c -o student.o

# Очищення
clean:
	rm -f *.o program
