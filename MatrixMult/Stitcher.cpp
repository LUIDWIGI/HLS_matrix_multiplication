#include "MatrixMult.hpp"
#include <cstdint>
#include <iostream>

void matrixAdder(matrix_out_t input_matrix[MATRIX_SIZE][MATRIX_SIZE],
                    matrix_out_t output_matrix[MATRIX_SIZE][MATRIX_SIZE])
{
//#pragma HLS INLINE
#pragma HLS pipeline ii=32
#pragma HLS ARRAY_PARTITION variable=output_matrix dim=0 type=complete
#pragma HLS ARRAY_PARTITION variable=input_matrix dim=0 type=complete
    for(uint16_t row=0; row<MATRIX_SIZE; ++row)
    {
        #pragma HLS LOOP_FLATTEN off=0
        for(uint16_t col=0; col<MATRIX_SIZE; ++col)
        {
            output_matrix[row][col]+=input_matrix[row][col];
        }
    }
}

void matrixStitcher(matrix_32_t input_4x4_matrix[MATRIX_SIZE][MATRIX_SIZE],
                        uint16_t size,
                        matrix_out_t* finalMatrix)
{
//#pragma HLS INLINE
#pragma HLS PIPELINE
    static uint16_t row_offset = 0, col_offset = 0;

    for(uint16_t row = 0; row<MATRIX_SIZE; ++row)
    {
        for(uint16_t col = 0; col<MATRIX_SIZE; ++col)
        {
            finalMatrix[(row+row_offset)*size + (col+col_offset)] = input_4x4_matrix[row][col];
        }
    }

    col_offset+=MATRIX_SIZE;

    if(col_offset >= size)
    {
        col_offset = 0;
        row_offset += MATRIX_SIZE;
    }
    
    if(row_offset >= size)
    {
        row_offset = 0;
    }


}