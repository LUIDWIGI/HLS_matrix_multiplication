#include "MatrixMult.hpp"
#include <cstdint>
#include <iostream>

typedef int16_t matrix_in_t;
typedef int16_t matrix_16_t;
typedef int32_t matrix_out_t;
typedef int32_t matrix_32_t;

void matrixSlicer(matrix_in_t* matrix_in_1,
                 matrix_in_t* matrix_in_2,
                 uint32_t size,
                 matrix_out_t matrix_out_1[MATRIX_SIZE][MATRIX_SIZE],
                 matrix_out_t matrix_out_2[MATRIX_SIZE][MATRIX_SIZE]);

void MatrixMult(matrix_in_t* matrix_in_1,
                matrix_in_t* matrix_in_2,
                uint16_t size,
                matrix_out_t* matrix_out)
{
#pragma HLS INTERFACE mode=m_axi port=matrix_out bundle=data
#pragma HLS INTERFACE mode=m_axi port=matrix_in_2 bundle=data
#pragma HLS INTERFACE mode=m_axi port=matrix_in_1 bundle=data
 
    for(uint16_t j=0; j<(size/MATRIX_SIZE)*(size/MATRIX_SIZE); ++j)
    {
        matrix_out_t Matrix_4x4_final[MATRIX_SIZE][MATRIX_SIZE] = {};
        matrix_32_t matrix_4x4_out[MATRIX_SIZE][MATRIX_SIZE];

        for(uint16_t i=0; i<(size/MATRIX_SIZE); ++i)
        {
            matrix_16_t Matrix_4x4_1[MATRIX_SIZE][MATRIX_SIZE];
            matrix_16_t Matrix_4x4_2[MATRIX_SIZE][MATRIX_SIZE];

            matrixSlicer(matrix_in_1, matrix_in_2, size, Matrix_4x4_1, Matrix_4x4_2);
            multiplier(Matrix_4x4_1, Matrix_4x4_2, matrix_4x4_out);
            matrixAdder(matrix_4x4_out, Matrix_4x4_final, size);
        }            
        matrixStitcher(Matrix_4x4_final, size, matrix_out);
    }
}