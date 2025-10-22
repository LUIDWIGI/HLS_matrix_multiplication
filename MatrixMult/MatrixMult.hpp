#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstdint>
#include <stdint.h>
#include <ap_int.h>
#include <iostream>
#include <assert.h>

#define MATRIX_SIZE 4
#define MAX_MATRIX_SIZE 4096

typedef int16_t matrix_in_t;
typedef int16_t matrix_16_t;
typedef int32_t matrix_out_t;
typedef int32_t matrix_32_t;

void MatrixMult(matrix_in_t* matrix_1,
                matrix_in_t* matrix_2,
                uint16_t size,
                matrix_out_t* matrix_out);

void matrixSlicer(matrix_in_t* matrix_in_1,
                    matrix_in_t* matrix_in_2,
                    uint32_t size,
                    matrix_16_t matrix_out_1[MATRIX_SIZE][MATRIX_SIZE],
                    matrix_16_t matrix_out_2[MATRIX_SIZE][MATRIX_SIZE]);

void multiplier(matrix_16_t matrix_in_1[MATRIX_SIZE][MATRIX_SIZE],
                    matrix_16_t matrix_in_2[MATRIX_SIZE][MATRIX_SIZE],
                    matrix_32_t matrix_out[MATRIX_SIZE][MATRIX_SIZE]);

void matrixAdder(matrix_out_t input_matrix[MATRIX_SIZE][MATRIX_SIZE],
                    matrix_out_t output_matrix[MATRIX_SIZE][MATRIX_SIZE]);

void matrixStitcher(matrix_32_t input_4x4_matrix[MATRIX_SIZE][MATRIX_SIZE],
                        uint16_t size,
                        matrix_out_t* finalMatrix);
#endif //MATRIX_HPP