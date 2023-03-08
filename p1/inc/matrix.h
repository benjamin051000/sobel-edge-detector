#ifndef _MATRIX_H
#define _MATRIX_H

/**
* An MxN matrix allocated on the heap.
* Contents can be accesssed via `my_matrix[r][c]`.
*/
typedef struct {
    unsigned M; // Rows
    unsigned N; // Cols
    int (*data)[]; // Data buffer
} matrix;

/**
* Create a new matrix.
* AKA "Constructor"
* NOTE: returned datatype is not cleared. You must popoulate the matrix yourself.
*/
matrix create_matrix(const unsigned M, const unsigned N);

/**
* "Destructor"
* Deletes internal data.
* NOTE: This calls `free()` on internal data.
*/
void destroy_matrix(matrix* m);

/**
* Print the matrix out.
* Uses a fancy preprocessor macro to also print the variable's name.
*/
#define print_matrix(A) (__print_matrix(#A, A))
void __print_matrix(const char *const name, const matrix *const m);

int* matrix_at(const matrix *const matrix, unsigned row, unsigned col);

#endif
