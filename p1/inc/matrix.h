#ifndef _MATRIX_H
#define _MATRIX_H

/**
* Print the matrix out.
* Uses a fancy preprocessor macro to also print the variable's name.
*/
#define print_matrix(A, M, N) (__print_matrix(#A, M, N, A))
void __print_matrix(const char *const name, const unsigned M, const unsigned N, int m[M][N]);

#endif
