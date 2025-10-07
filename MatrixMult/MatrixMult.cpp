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
    {   
        for(uint16_t j=0; j<(size/MATRIX_SIZE)*(size/MATRIX_SIZE); ++j)
        {
            matrix_out_t Matrix_4x4_final[MATRIX_SIZE][MATRIX_SIZE] = {};
            matrix_32_t matrix_4x4_out[MATRIX_SIZE][MATRIX_SIZE] = {};

            for(uint16_t i=0; i<(size/MATRIX_SIZE); ++i)
            {
                matrix_16_t Matrix_4x4_1[MATRIX_SIZE][MATRIX_SIZE];
                matrix_16_t Matrix_4x4_2[MATRIX_SIZE][MATRIX_SIZE];

                matrixSlicer(matrix_in_1, matrix_in_2, size, Matrix_4x4_1, Matrix_4x4_2);
                multiplier(Matrix_4x4_1, Matrix_4x4_2, matrix_4x4_out);
                matrixAdder(matrix_4x4_out, Matrix_4x4_final, size);
            }
            std::cout << "Resultant 4x4 Matrix Block: " << std::endl;
            for (uint16_t row = 0; row < MATRIX_SIZE; ++row) {
                for (uint16_t col = 0; col < MATRIX_SIZE; ++col) {
                    std::cout << Matrix_4x4_final[row][col] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "." <<std::endl << "." << std::endl;
            
            matrixStitcher(Matrix_4x4_final, size, matrix_out);
        }
    }
}