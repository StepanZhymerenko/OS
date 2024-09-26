// src/arraylist.h

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#define INITIAL_CAPACITY 4  // Початкова ємність масиву

typedef struct {
    int *data;
    int size;
    int capacity;
} ArrayList;

// Функції для роботи зі списком
ArrayList* createList();
void resize(ArrayList *list);
void add(ArrayList *list, int item);
void insert(ArrayList *list, int index, int item);
int size(ArrayList *list);
void removeAt(ArrayList *list, int index);
void set(ArrayList *list, int index, int item);
int get(ArrayList *list, int index);
void freeList(ArrayList *list);

#endif // ARRAYLIST_H
