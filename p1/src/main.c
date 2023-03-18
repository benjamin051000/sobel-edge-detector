#include "error_codes.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #define DEBUG
#include "common.h"

/* Find the time difference. */
double tdiff(struct timespec a, struct timespec b) {
    return (double)( b.tv_sec - a.tv_sec ) + (double)( b.tv_nsec - a.tv_nsec ) / 1E9;
}

/* Return the current time. */
struct timespec now(void) {
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return t;
}

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


/**
* Apply the sobel edge detection filter algorithm on matrix input.
* Side effect: Modifies matrix output.
*/
void sobel_edge(const unsigned M, const unsigned N, int input[M][N], int result[M][N]) {
    // Iterate from (1, 1) to (M-1, N-1)
    for(unsigned r = 1; r < M - 1; r++) {
        for(unsigned c = 1; c < N - 1; c++) {
            // Defitions of neighboring tiles:
            // p1 p2 p3
            // q1 q2 q3
            // r1 r2 r3

            const int p1 = input[r-1][c-1], // Top left
            p2 = input[r-1][c], // Top center
            p3 = input[r-1][c+1], // Top right
            r1 = input[r+1][c-1], // Bottom left
            r2 = input[r+1][c], // Bottom center
            r3 = input[r+1][c+1], // Bottom right
            q1 = input[r][c-1], // Center left
            // q2 = center, frame of reference
            q3 = input[r][c+1]; // Center right

            const int horizontal = abs((p1 - r1) + 2 * (p2 - r2) + (p3 - r3));
            const int vertical = abs((p1 - p3) + 2 * (q1 - q3) + (r1 - r3));

            result[r][c] = horizontal + vertical;
        }
    }
}


int main(void) {
    DP("Starting up...\n");

    // const unsigned M = 10;
    // const unsigned N = 10;
    // int A[M][N];
    //
    // for(unsigned r = 0; r < M; r++)
    //     for(unsigned c = 0; c < N; c++)
    //        A[r][c] = (int)M * (int)r + (int)c;
    //
    // print_matrix(A, M, N);
    //
    // printf("-----------------------------------------\n");

    const unsigned img_M = 5000;
    const unsigned img_N = 5000;
    int input[img_M][img_N];
    load_image("../input.txt", img_M, img_N, input);
    DBG(print_matrix(input, img_M, img_N);)

    int output[img_M][img_N];
    struct timespec start = now();
    sobel_edge(img_M, img_N, input, output);
    struct timespec end = now();
    DBG(print_matrix(output, img_M, img_N);)
    save_image("../output.txt", img_M, img_N, output);

    double elapsed_time = tdiff(start, end);
    printf("Elapsed time: %.8f sec\n", elapsed_time);

#ifdef OMPI_MPI_H
    MPI_Finalize();
#endif
    printf("Goodbye.\n");
    return 0;
}

