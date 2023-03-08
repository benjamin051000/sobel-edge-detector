#include "common.h"
#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

/**
* Create a new matrix.
* AKA "Constructor"
* NOTE: returned datatype is not cleared. You must popoulate the matrix yourself.
*/
matrix create_matrix(const unsigned M, const unsigned N) {
    // Create the buffer.
    // Using epic c99 array pointer syntax :D
    // see https://stackoverflow.com/questions/32050256/function-to-dynamically-allocate-matrix
    // for an explanation of this type
    int (*data)[N] = malloc(sizeof(int[M][N]));

    // Check for failed malloc
    if (data == NULL) {
        fprintf(stderr, "ERROR: Couldn't allocate new matrix_t.\n");
        // Abort MPI if we are using that
#ifdef OMPI_MPI_H
        MPI_Abort(MPI_COMM_WORLD, ERR_BAD_MALLOC);
#else
        // Quit
        exit(ERR_BAD_MALLOC);
#endif

    }

    return (matrix) {
        .M = M,
        .N = N,
        .data = data
    };
}

/**
* "Destructor"
* Deletes internal data.
* NOTE: This calls `free()` on internal data.
* NOTE: argument passed in is effectively consumed.
*/
void destroy_matrix(matrix* m) {
    free(m->data);
}


void __print_matrix(const char *const name, const matrix *const m) {
    printf("========== Matrix %s ==========\n", name);
    // Cast m->data to an array pointer with N cols
    // int (*data)[m->N] = m->data;

    for(unsigned r = 0; r < m->M; r++) {
        for(unsigned c = 0; c < m->N; c++) {
            printf("%3d ", *matrix_at(m, r, c));
        }
        printf("\n");
    }
    printf("========== End of %s ==========\n", name);
}


int* matrix_at(const matrix *const matrix, unsigned row, unsigned col) {
    int (*data)[matrix->N] = matrix->data;
    return &data[row][col];
}

