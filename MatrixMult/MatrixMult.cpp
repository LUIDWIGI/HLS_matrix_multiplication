#include "MatrixMult.hpp"
#include <cstdint>
#include <iostream>

void MatrixMult(matrix_in_t* matrix_in_1,
                matrix_in_t* matrix_in_2,
                uint16_t size,
                matrix_out_t* matrix_out)
{
    if (size<=MATRIX_SIZE)
    {
        matrix_16_t matrix_temp_1[MATRIX_SIZE][MATRIX_SIZE];
        matrix_16_t matrix_temp_2[MATRIX_SIZE][MATRIX_SIZE];

        matrix_out_t matrix_temp_3[MATRIX_SIZE][MATRIX_SIZE];

        for (uint16_t i=0; i<MATRIX_SIZE; i++)
        {
            #pragma HLS unroll
            for(uint16_t j=0; j<MATRIX_SIZE; j++)
            {
                matrix_temp_1[i][j] = matrix_in_1[i*MATRIX_SIZE+j];
                matrix_temp_2[i][j] = matrix_in_2[i*MATRIX_SIZE+j];
            }
        }

        multiplier(matrix_temp_1, matrix_temp_2, matrix_temp_3);

        for (uint16_t i=0; i<MATRIX_SIZE; i++)
        {
            #pragma HLS unroll
            for(uint16_t j=0; j<MATRIX_SIZE; j++)
            {
                matrix_out[i*MATRIX_SIZE+j] = matrix_temp_3[i][j];
            }
        }
    }
    else 
    {   for(uint16_t i=0; i<size/4; ++i)
        {
            matrix_16_t matrix_temp_1[MATRIX_SIZE][MATRIX_SIZE];
            matrix_16_t matrix_temp_2[MATRIX_SIZE][MATRIX_SIZE];

            matrix_out_t matrix_temp_3[MATRIX_SIZE][MATRIX_SIZE];

            matrixSlicer(matrix_in_1, matrix_in_2, size, matrix_temp_1, matrix_temp_2);
            multiplier(matrix_temp_1, matrix_temp_2, matrix_temp_3);
        }
    }
}