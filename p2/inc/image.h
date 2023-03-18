#ifndef _IMAGE_H
#define _IMAGE_H

void load_image(const char *const filename, const unsigned M, const unsigned N, int m[M][N]);

void save_image(const char *const filename, const unsigned M, const unsigned N, int matrix[M][N]);

#endif
