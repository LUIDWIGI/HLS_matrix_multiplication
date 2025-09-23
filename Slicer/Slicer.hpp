#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstdint>
#include <stdint.h>
#include <ap_int.h>

#define MATRIX_SIZE 4

typedef int16_t matrix_in_t;
typedef int16_t matrix_out_t;

void matrixSlicer(matrix_in_t* matrix_in_1,
                 matrix_in_t* matrix_in_2,
                 uint32_t size,
                 matrix_out_t matrix_out_1[MATRIX_SIZE][MATRIX_SIZE],
                 matrix_out_t matrix_out_2[MATRIX_SIZE][MATRIX_SIZE]);
#endif //MATRIX_HPP