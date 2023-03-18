#include <stdio.h>
#include <stdlib.h>
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

void save_image(const char *const filename, const unsigned M, const unsigned N, int matrix[M][N]) {
    FILE *fp = fopen(filename, "w");

    if(fp == NULL) {
        fprintf(stderr, "ERROR: Couldn't open output file!\n");

#ifdef OMPI_MPI_H
        MPI_Abort(MPI_COMM_WORLD, ERR_NO_OUTPUT_FILE);
#else
        exit(ERR_NO_OUTPUT_FILE);
#endif
    }

    for(unsigned r = 0; r < M; r++) {
        for(unsigned c = 0; c < N; c++) {
            const int val = matrix[r][c];
            // Write the value to the file.
            fprintf(fp, "%d ", val);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

