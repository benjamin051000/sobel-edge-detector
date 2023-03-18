#include <stdio.h>
#include <stdlib.h>
// #define DEBUG
#include "common.h"


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

