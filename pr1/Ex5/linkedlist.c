#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

// Створення нового списку
LinkedList* createList() {
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

// Додавання елемента в кінець списку
void add(LinkedList *list, int item) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    list->size++;
}

// Вставка елемента в середину списку
void insert(LinkedList *list, int index, int item) {
    if (index < 0 || index > list->size) {
        printf("Індекс виходить за межі\n");
        return;
    }

    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node *temp = list->head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
    list->size++;
}

// Отримання кількості елементів у списку
int size(LinkedList *list) {
    return list->size;
}

// Видалення елемента по індексу
void removeAt(LinkedList *list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Індекс виходить за межі\n");
        return;
    }

    Node *temp = list->head;

    if (index == 0) {
        list->head = temp->next;
        free(temp);
    } else {
        Node *prev = NULL;
        for (int i = 0; i < index; i++) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
        free(temp);
    }
    list->size--;
}

// Зміна значення елемента за індексом
void set(LinkedList *list, int index, int item) {
    if (index < 0 || index >= list->size) {
        printf("Індекс виходить за межі\n");
        return;
    }

    Node *temp = list->head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    temp->data = item;
}

// Отримання елемента за індексом
int get(LinkedList *list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Індекс виходить за межі\n");
        return -1;  // Значення помилки
    }

    Node *temp = list->head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp->data;
}

// Звільнення пам'яті
void freeList(LinkedList *list) {
    Node *current = list->head;
    Node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
}
