#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <stdint.h>
#include <ap_int.h>

#define MATRIX_SIZE 4

typedef int16_t matrix_in_t;
typedef int32_t matrix_out_t;

void matrix_mult(matrix_in_t matrix_in_1[MATRIX_SIZE][MATRIX_SIZE],
                 matrix_in_t matrix_in_2[MATRIX_SIZE][MATRIX_SIZE],
                 matrix_out_t matrix_out[MATRIX_SIZE][MATRIX_SIZE]);
#endif //MATRIX_HPP