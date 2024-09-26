// src/arraylist.c

#include <stdio.h>
#include <stdlib.h>
#include "arraylist.h"

// Створення нового списку
ArrayList* createList() {
    ArrayList *list = (ArrayList*)malloc(sizeof(ArrayList));
    list->data = (int*)malloc(INITIAL_CAPACITY * sizeof(int));
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    return list;
}

// Збільшення ємності списку
void resize(ArrayList *list) {
    list->capacity *= 2;
    list->data = (int*)realloc(list->data, list->capacity * sizeof(int));
}

// Додавання елемента в кінець списку
void add(ArrayList *list, int item) {
    if (list->size == list->capacity) {
        resize(list);
    }
    list->data[list->size++] = item;
}

// Вставка елемента в середину списку
void insert(ArrayList *list, int index, int item) {
    if (index < 0 || index > list->size) {
        printf("Індекс виходить за межі\n");
        return;
    }
    if (list->size == list->capacity) {
        resize(list);
    }
    for (int i = list->size; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = item;
    list->size++;
}

// Отримання кількості елементів у списку
int size(ArrayList *list) {
    return list->size;
}

// Видалення елемента по індексу
void removeAt(ArrayList *list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Індекс виходить за межі\n");
        return;
    }
    for (int i = index; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->size--;
}

// Зміна значення елемента за індексом
void set(ArrayList *list, int index, int item) {
    if (index < 0 || index >= list->size) {
        printf("Індекс виходить за межі\n");
        return;
    }
    list->data[index] = item;
}

// Отримання елемента за індексом
int get(ArrayList *list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Індекс виходить за межі\n");
        return -1;  // Значення помилки
    }
    return list->data[index];
}

// Звільнення пам'яті
void freeList(ArrayList *list) {
    free(list->data);
    free(list);
}
