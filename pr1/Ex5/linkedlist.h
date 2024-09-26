#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Структура для вузла списку
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Структура для зв'язного списку
typedef struct {
    Node *head;
    int size;
} LinkedList;

// Оголошення функцій для роботи зі списком
LinkedList* createList();
void add(LinkedList *list, int item);
void insert(LinkedList *list, int index, int item);
int size(LinkedList *list);
void removeAt(LinkedList *list, int index);
void set(LinkedList *list, int index, int item);
int get(LinkedList *list, int index);
void freeList(LinkedList *list);

#endif // LINKEDLIST_H
