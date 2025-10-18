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
#pragma HLS INTERFACE mode=m_axi port=matrix_in_1 depth=(MAX_MATRIX_SIZE*MAX_MATRIX_SIZE) max_widen_bitwidth=64 bundle=matrix_a
#pragma HLS INTERFACE mode=m_axi port=matrix_in_2 depth=(MAX_MATRIX_SIZE*MAX_MATRIX_SIZE) max_widen_bitwidth=64 bundle=matrix_b
#pragma HLS INTERFACE mode=m_axi port=matrix_out depth=(MAX_MATRIX_SIZE*MAX_MATRIX_SIZE) max_widen_bitwidth=64 bundle=matrix_c
 
    for(uint16_t j=0; j<(size/MATRIX_SIZE)*(size/MATRIX_SIZE); ++j)
    {
    #pragma HLS dataflow
    #pragma HLS LOOP_TRIPCOUNT max=(MAX_MATRIX_SIZE/MATRIX_SIZE * MAX_MATRIX_SIZE/MATRIX_SIZE)
        matrix_out_t Matrix_4x4_final[MATRIX_SIZE][MATRIX_SIZE] = {};
        #pragma HLS ARRAY_PARTITION variable=Matrix_4x4_final dim=0 type=complete   
        for(uint16_t i=0; i<(size/MATRIX_SIZE); ++i)
        {
            #pragma HLS LOOP_TRIPCOUNT max=MAX_MATRIX_SIZE/MATRIX_SIZE
            #pragma HLS PIPELINE
            matrix_16_t Matrix_4x4_1[MATRIX_SIZE][MATRIX_SIZE];
            matrix_16_t Matrix_4x4_2[MATRIX_SIZE][MATRIX_SIZE];
            matrix_32_t matrix_4x4_out[MATRIX_SIZE][MATRIX_SIZE];


            matrixSlicer(matrix_in_1, matrix_in_2, size, Matrix_4x4_1, Matrix_4x4_2);
            multiplier(Matrix_4x4_1, Matrix_4x4_2, matrix_4x4_out);
            matrixAdder(matrix_4x4_out, Matrix_4x4_final);
        }        
        matrixStitcher(Matrix_4x4_final, size, matrix_out);
    }
}