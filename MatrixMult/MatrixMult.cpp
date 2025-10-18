#include "MatrixMult.hpp"
#include <cstdint>
#include <iostream>

typedef int16_t matrix_in_t;
typedef int16_t matrix_16_t;
typedef int32_t matrix_out_t;
typedef int32_t matrix_32_t;

void MatrixMult(matrix_in_t* matrix_in_1,
                matrix_in_t* matrix_in_2,
                uint16_t size,
                matrix_out_t* matrix_out)
{
#pragma HLS INTERFACE mode=m_axi port=matrix_in_1 bundle=BUS_A channel=0 depth=(MAX_MATRIX_SIZE*MAX_MATRIX_SIZE)
#pragma HLS INTERFACE mode=m_axi port=matrix_in_2 bundle=BUS_A channel=1 depth=(MAX_MATRIX_SIZE*MAX_MATRIX_SIZE)
#pragma HLS INTERFACE mode=m_axi port=matrix_out bundle=BUS_A channel=0 depth=(MAX_MATRIX_SIZE*MAX_MATRIX_SIZE)

    matrix_in_t matrix1[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
    matrix_in_t matrix2[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
#pragma HLS ARRAY_PARTITION variable=matrix2 dim=0 type=complete
#pragma HLS ARRAY_PARTITION variable=matrix1 dim=0 type=complete

    for (uint16_t x=0; x<size; ++x)
    {
        for(uint16_t y=0; y<size; ++y)
        {
            matrix1[x][y] = matrix_in_1[x*size+y];
            matrix2[x][y] = matrix_in_2[x*size+y];
            std::cout << matrix2[x][y] << " ";
        }
        std::cout << std::endl;
    }
 
    for(uint16_t j=0; j<(size/MATRIX_SIZE)*(size/MATRIX_SIZE); ++j)
    {
        matrix_out_t Matrix_4x4_final[MATRIX_SIZE][MATRIX_SIZE] = {};
        matrix_32_t matrix_4x4_out[MATRIX_SIZE][MATRIX_SIZE];
        for(uint16_t i=0; i<(size/MATRIX_SIZE); ++i)
        {
            matrix_16_t Matrix_4x4_1[MATRIX_SIZE][MATRIX_SIZE];
            matrix_16_t Matrix_4x4_2[MATRIX_SIZE][MATRIX_SIZE];

            matrixSlicer(&matrix1[0][0], &matrix2[0][0], size, Matrix_4x4_1, Matrix_4x4_2);
            multiplier(Matrix_4x4_1, Matrix_4x4_2, matrix_4x4_out);
            matrixAdder(matrix_4x4_out, Matrix_4x4_final);
        }            
        matrixStitcher(Matrix_4x4_final, size, matrix_out);
    }
}