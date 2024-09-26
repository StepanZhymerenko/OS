# Компілятор та флаги компіляції
CC = gcc
CFLAGS = -Wall -g

# Ціль за замовчуванням
all: program

# Створення виконуваного файлу з лінкуванням бібліотеки math (-lm)
program: main.o process_points.o point_utils.o
	$(CC) $(CFLAGS) -o program main.o point_utils.o process_points.o -lm

# Правило для компіляції main.c
main.o: main.c point_utils.c process_points.c
	$(CC) $(CFLAGS) -c main.c -o main.o

# Правило для компіляції point_utils.c
point_utils.o: point_utils.c point_utils.h
	$(CC) $(CFLAGS) -c point_utils.c -o point_utils.o
 
# Правило для компіляції process_points.c
process_points.o: process_points.c process_points.h
	$(CC) $(CFLAGS) -c process_points.c -o process_points.o

# Очищення
clean:
	rm -f *.o program
