#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Matrix* create_matrix(int rows, int cols) {
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        matrix->data[i] = (double*)malloc(cols * sizeof(double));
    }
    return matrix;
}

void delete_matrix(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

Matrix* resize_matrix(Matrix* matrix, int new_rows, int new_cols) {
    Matrix* new_matrix = create_matrix(new_rows, new_cols);
    int min_rows = (new_rows < matrix->rows) ? new_rows : matrix->rows;
    int min_cols = (new_cols < matrix->cols) ? new_cols : matrix->cols;

    for (int i = 0; i < min_rows; i++) {
        for (int j = 0; j < min_cols; j++) {
            new_matrix->data[i][j] = matrix->data[i][j];
        }
    }

    delete_matrix(matrix);
    return new_matrix;
}

int get_rows(Matrix* matrix) {
    return matrix->rows;
}

int get_cols(Matrix* matrix) {
    return matrix->cols;
}

void set_element(Matrix* matrix, int row, int col, double value) {
    if (row < matrix->rows && col < matrix->cols) {
        matrix->data[row][col] = value;
    }
}

double get_element(Matrix* matrix, int row, int col) {
    if (row < matrix->rows && col < matrix->cols) {
        return matrix->data[row][col];
    }
    return 0;
}

void print_matrix(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%f ", matrix->data[i][j]);
        }
        printf("\n");
    }
}

int save_matrix_to_file(Matrix* matrix, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) return -1;

    fprintf(file, "%d %d\n", matrix->rows, matrix->cols);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            fprintf(file, "%f ", matrix->data[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return 0;
}

Matrix* load_matrix_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) return NULL;

    int rows, cols;
    fscanf(file, "%d %d", &rows, &cols);
    Matrix* matrix = create_matrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(file, "%lf", &matrix->data[i][j]);
        }
    }
    fclose(file);
    return matrix;
}

Matrix* add_matrices(Matrix* m1, Matrix* m2) {
    if (m1->rows != m2->rows || m1->cols != m2->cols) return NULL;

    Matrix* result = create_matrix(m1->rows, m1->cols);
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->cols; j++) {
            result->data[i][j] = m1->data[i][j] + m2->data[i][j];
        }
    }
    return result;
}

Matrix* subtract_matrices(Matrix* m1, Matrix* m2) {
    if (m1->rows != m2->rows || m1->cols != m2->cols) return NULL;

    Matrix* result = create_matrix(m1->rows, m1->cols);
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->cols; j++) {
            result->data[i][j] = m1->data[i][j] - m2->data[i][j];
        }
    }
    return result;
}

Matrix* multiply_matrix_by_scalar(Matrix* matrix, double scalar) {
    Matrix* result = create_matrix(matrix->rows, matrix->cols);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            result->data[i][j] = matrix->data[i][j] * scalar;
        }
    }
    return result;
}

Matrix* multiply_matrices(Matrix* m1, Matrix* m2) {
    if (m1->cols != m2->rows) return NULL;

    Matrix* result = create_matrix(m1->rows, m2->cols);
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m2->cols; j++) {
            result->data[i][j] = 0;
            for (int k = 0; k < m1->cols; k++) {
                result->data[i][j] += m1->data[i][k] * m2->data[k][j];
            }
        }
    }
    return result;
}

Matrix* transpose_matrix(Matrix* matrix) {
    Matrix* result = create_matrix(matrix->cols, matrix->rows);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            result->data[j][i] = matrix->data[i][j];
        }
    }
    return result;
}
