#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

// Функція для виведення всіх елементів списку
void printList(LinkedList *list) {
    Node *temp = list->head;
    printf("Елементи списку:\n");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    LinkedList *list = createList();

    // Додавання елементів
    printf("Додаємо елементи: 10, 20, 30, 40\n");
    add(list, 10);
    add(list, 20);
    add(list, 30);
    add(list, 40);
    printList(list);  // Виведення списку

    // Вставка елемента
    printf("Вставляємо елемент 25 на індекс 2\n");
    insert(list, 2, 25);
    printList(list);

    // Отримання елемента
    printf("Значення елемента на індексі 3: %d\n", get(list, 3));

    // Зміна елемента
    printf("Змінюємо елемент на індексі 1 на 15\n");
    set(list, 1, 15);
    printList(list);

    // Видалення елемента
    printf("Видаляємо елемент на індексі 3\n");
    removeAt(list, 3);
    printList(list);

    // Виведення кількості елементів
    printf("Кількість елементів у списку: %d\n", size(list));

    // Звільнення пам'яті
    freeList(list);

    return 0;
}
