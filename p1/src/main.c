#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#define DEBUG
#include "common.h"

/**
* load the input text file.
*/
matrix load_image(void) {
    // Open the file
    FILE *fp = fopen("../input.txt", "r");

    // Ensure file opened
    if (fp == NULL) {
        fprintf(stderr, "ERROR: Couldn't open input file!\n");

#ifdef OMPI_MPI_H
        MPI_Abort(MPI_COMM_WORLD, ERR_NO_INPUT_FILE);
#else
        exit(ERR_NO_INPUT_FILE);
#endif
    }

    matrix m = create_matrix(5, 5);

    for(unsigned r = 0; r < m.M; r++) {
        for(unsigned c = 0; c < m.N; c++) {
            // Read the next word from the file.
            char word[4];
            // we know the inputs are 8-bits, so they'll always be 3 digits long.
            if(fscanf(fp, "%3s", word)) {
                *matrix_at(&m, r, c) = atof(word);
            }
            else {
                DP("Something went wrong while reading words from the file.\n");
#ifdef OMPI_MPI_H
                MPI_Abort(MPI_COMM_WORLD, ERR_INPUT_PARSING);
#else
                exit(ERR_INPUT_PARSING);
#endif
            }
        }
    }

    fclose(fp);
    return m;
}

int main(void) {
    DP("Hello, world!\n");
    int a = 5;
    DP("a: %d\n", a);

    matrix A = create_matrix(4, 4);

    for(unsigned r = 0; r < A.M; r++)
        for(unsigned c = 0; c < A.N; c++)
           *matrix_at(&A, r, c) = A.M * r + c;

    print_matrix(&A);
    destroy_matrix(&A);

    printf("-------------------------------\n");

    matrix input = load_image();
    print_matrix(&input);
    destroy_matrix(&input);

    return 0;
}

