#include <stdio.h>
#include "matrix.h"

int main() {
    // 1. Створення матриці 2x2
    Matrix* matrix1 = create_matrix(2, 2);
    set_element(matrix1, 0, 0, 1.0);
    set_element(matrix1, 0, 1, 2.0);
    set_element(matrix1, 1, 0, 3.0);
    set_element(matrix1, 1, 1, 4.0);

    printf("Matrix 1 (2x2):\n");
    print_matrix(matrix1);
    
    // 2. Зміна розміру матриці (розширюємо до 3x3)
    matrix1 = resize_matrix(matrix1, 3, 3);
    set_element(matrix1, 2, 2, 5.0);  // Додаємо новий елемент після зміни розміру
    printf("\nMatrix 1 після зміни розміру (3x3):\n");
    print_matrix(matrix1);

    // 3. Визначення кількості рядків і стовпців
    printf("\nMatrix 1 має %d рядків і %d стовпців\n", get_rows(matrix1), get_cols(matrix1));

    // 4. Створення іншої матриці 3x3 для арифметичних операцій
    Matrix* matrix2 = create_matrix(3, 3);
    set_element(matrix2, 0, 0, 6.0);
    set_element(matrix2, 0, 1, 7.0);
    set_element(matrix2, 0, 2, 8.0);
    set_element(matrix2, 1, 0, 9.0);
    set_element(matrix2, 1, 1, 10.0);
    set_element(matrix2, 1, 2, 11.0);
    set_element(matrix2, 2, 0, 12.0);
    set_element(matrix2, 2, 1, 13.0);
    set_element(matrix2, 2, 2, 14.0);

    printf("\nMatrix 2 (3x3):\n");
    print_matrix(matrix2);

    // 5. Додавання матриць
    Matrix* sum_matrix = add_matrices(matrix1, matrix2);
    if (sum_matrix != NULL) {
        printf("\nSum of Matrix 1 and Matrix 2:\n");
        print_matrix(sum_matrix);
    } else {
        printf("\nДодавання не вдалося. Розміри матриць не співпадають.\n");
    }

    // 6. Віднімання матриць
    Matrix* diff_matrix = subtract_matrices(matrix1, matrix2);
    if (diff_matrix != NULL) {
        printf("\nDifference of Matrix 1 and Matrix 2:\n");
        print_matrix(diff_matrix);
    } else {
        printf("\nВіднімання не вдалося. Розміри матриць не співпадають.\n");
    }

    // 7. Множення матриці на скаляр
    Matrix* scalar_matrix = multiply_matrix_by_scalar(matrix1, 2.0);
    printf("\nMatrix 1 помножена на скаляр 2.0:\n");
    print_matrix(scalar_matrix);

    // 8. Множення двох матриць
    Matrix* product_matrix = multiply_matrices(matrix1, matrix2);
    if (product_matrix != NULL) {
        printf("\nProduct of Matrix 1 and Matrix 2:\n");
        print_matrix(product_matrix);
    } else {
        printf("\nМноження не вдалося. Кількість стовпців першої матриці не дорівнює кількості рядків другої.\n");
    }

    // 9. Транспонування матриці
    Matrix* transposed_matrix = transpose_matrix(matrix1);
    printf("\nTransposed Matrix 1:\n");
    print_matrix(transposed_matrix);

    // 10. Збереження матриці у файл
    if (save_matrix_to_file(matrix1, "matrix1.txt") == 0) {
        printf("\nMatrix 1 збережено у файл matrix1.txt\n");
    }

    // 11. Читання матриці з файлу
    Matrix* loaded_matrix = load_matrix_from_file("matrix1.txt");
    if (loaded_matrix != NULL) {
        printf("\nМатриця, завантажена з файлу:\n");
        print_matrix(loaded_matrix);
    }

    // Очищення пам'яті
    delete_matrix(matrix1);
    delete_matrix(matrix2);
    delete_matrix(sum_matrix);
    delete_matrix(diff_matrix);
    delete_matrix(scalar_matrix);
    delete_matrix(product_matrix);
    delete_matrix(transposed_matrix);
    delete_matrix(loaded_matrix);

    return 0;
}
