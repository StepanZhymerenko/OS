#include <stdio.h>
#include <stdlib.h>
#include "arraylist.h"

// Функція для виведення всіх елементів списку
void printList(ArrayList *list) {
    printf("Елементи списку:\n");
    for (int i = 0; i < size(list); i++) {
        printf("%d ", get(list, i));
    }
    printf("\n");
}

int main() {
    ArrayList *list = createList();

    // Додавання елементів
    printf("Додаємо елементи: 10, 20, 30, 40\n");
    add(list, 10);
    printList(list);  // Виведення після додавання 10
    add(list, 20);
    printList(list);  // Виведення після додавання 20
    add(list, 30);
    printList(list);  // Виведення після додавання 30
    add(list, 40);
    printList(list);  // Виведення після додавання 40

    // Додаємо ще один елемент в кінець списку
    printf("Додаємо елемент 50 в кінець списку\n");
    add(list, 50);
    printList(list);  // Виведення після додавання 50

    // Отримання значення за індексом
    int index = 3;
    printf("Значення елемента на індексі %d: %d\n", index, get(list, index));

    // Вставка елемента
    printf("Вставляємо елемент 25 на індекс 2\n");
    insert(list, 2, 25);
    printList(list);  // Виведення після вставки 25

    // Отримання кількості елементів
    printf("Кількість елементів у списку: %d\n", size(list));

    // Зміна елемента
    printf("Змінюємо елемент на індексі 1 на 15\n");
    set(list, 1, 15);
    printf("Елемент на індексі 1 після зміни: %d\n", get(list, 1));
    printList(list);  // Виведення після зміни елемента

    // Видалення елемента
    printf("Видаляємо елемент на індексі 3\n");
    removeAt(list, 3);
    printList(list);  // Виведення після видалення елемента

    // Звільнення пам'яті
    freeList(list);

    return 0;
}
