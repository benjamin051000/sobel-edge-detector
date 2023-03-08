#include <stdio.h>
#define DEBUG
#include "common.h"


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

    return 0;
}

