#include <stdio.h>
#include <stdlib.h>
#define DEBUG
#include "common.h"

/**
* load the input text file into a matrix.
* Side effect: Modifies matrix m.
*/
void load_image(const char *const filename, const unsigned M, const unsigned N, int m[M][N]) {
    // Open the file
    FILE *fp = fopen(filename, "r");

    // Ensure file opened
    if (fp == NULL) {
        fprintf(stderr, "ERROR: Couldn't open input file!\n");

#ifdef OMPI_MPI_H
        MPI_Abort(MPI_COMM_WORLD, ERR_NO_INPUT_FILE);
#else
        exit(ERR_NO_INPUT_FILE);
#endif
    }

    for(unsigned r = 0; r < M; r++) {
        for(unsigned c = 0; c < N; c++) {
            // Read the next word from the file.
            char word[4];
            // we know the inputs are 8-bits, so they'll always be 3 digits long.
            if(fscanf(fp, "%3s", word)) {
                // Cast the value to an int and store it
                m[r][c] = (int)strtol(word, NULL, 10);
            }
            else {
                DP("Something went wrong while reading words from the file.\n");
                fclose(fp);
#ifdef OMPI_MPI_H
                MPI_Abort(MPI_COMM_WORLD, ERR_INPUT_PARSING);
#else
                exit(ERR_INPUT_PARSING);
#endif
            } // end of else
        } // end of for c 
    } // end of for r 

    fclose(fp);
}


int main(void) {
    DP("Starting up...\n");

    const unsigned M = 10;
    const unsigned N = 10;
    int A[M][N];

    for(unsigned r = 0; r < M; r++)
        for(unsigned c = 0; c < N; c++)
           A[r][c] = (int)M * (int)r + (int)c;

    print_matrix(A, M, N);

    printf("-----------------------------------------\n");

    const unsigned img_M = 25;
    const unsigned img_N = 25;
    int input[img_M][img_N];
    load_image("../input.txt", img_M, img_N, input);
    print_matrix(input, img_M, img_N);

#ifdef OMPI_MPI_H
    MPI_Finalize();
#endif
    printf("Goodbye.\n");
    return 0;
}

