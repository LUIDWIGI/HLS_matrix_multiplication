#include "MatrixMult.hpp"
#include <cstdint>
#include <iostream>

void matrixAdder(matrix_out_t input_matrix[MATRIX_SIZE][MATRIX_SIZE],
                    matrix_out_t output_matrix[MATRIX_SIZE][MATRIX_SIZE],
                    uint16_t size)
{
    for(uint16_t row=0; row<MATRIX_SIZE; ++row)
    {
        for(uint16_t col=0; col<MATRIX_SIZE; ++col)
        {
            output_matrix[row][col]+=input_matrix[row][col];
        }
    }
}