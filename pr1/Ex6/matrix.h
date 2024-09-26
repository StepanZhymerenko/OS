#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int rows;
    int cols;
    double** data;
} Matrix;

// Функції для роботи з матрицями
Matrix* create_matrix(int rows, int cols);
void delete_matrix(Matrix* matrix);
Matrix* resize_matrix(Matrix* matrix, int new_rows, int new_cols);
int get_rows(Matrix* matrix);
int get_cols(Matrix* matrix);
void set_element(Matrix* matrix, int row, int col, double value);
double get_element(Matrix* matrix, int row, int col);
void print_matrix(Matrix* matrix);
int save_matrix_to_file(Matrix* matrix, const char* filename);
Matrix* load_matrix_from_file(const char* filename);

// Операції над матрицями
Matrix* add_matrices(Matrix* m1, Matrix* m2);
Matrix* subtract_matrices(Matrix* m1, Matrix* m2);
Matrix* multiply_matrix_by_scalar(Matrix* matrix, double scalar);
Matrix* multiply_matrices(Matrix* m1, Matrix* m2);
Matrix* transpose_matrix(Matrix* matrix);

#endif
