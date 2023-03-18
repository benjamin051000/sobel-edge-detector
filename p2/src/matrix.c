#include "common.h"
#include <stdlib.h>
#include <stdio.h>

void __print_matrix(const char *const name, const unsigned M, const unsigned N, int m[M][N]) {
    printf("========== Matrix %s ==========\n", name);
    // Cast m->data to an array pointer with N cols
    // int (*data)[m->N] = m->data;

    for(unsigned r = 0; r < M; r++) {
        for(unsigned c = 0; c < N; c++) {
            printf("%3d ", m[r][c]);
        }
        printf("\n");
    }
    printf("========== End of %s ==========\n", name);
}

