#include "MatrixMult.hpp"
#include <cstdint>
#include <iostream>

typedef int16_t matrix_in_t;
typedef int16_t matrix_16_t;
typedef int32_t matrix_out_t;
typedef int32_t matrix_32_t;

void MatrixMult_NoCache(matrix_in_t* matrix_in_1,
                matrix_in_t* matrix_in_2,
                uint16_t size,
                matrix_out_t* matrix_out)
{
#pragma HLS INTERFACE s_axilite port=size bundle=ctrl
#pragma HLS INTERFACE s_axilite port=return bundle=ctrl
// #pragma HLS CACHE port=matrix_in_2 depth=MAX_MATRIX_SIZE lines=MATRIX_SIZE*4
// #pragma HLS CACHE port=matrix_in_1 depth=MAX_MATRIX_SIZE lines=MATRIX_SIZE*4
    assert(size%2==0);
#pragma HLS INTERFACE mode=m_axi port=matrix_in_1 bundle=matrix_a depth=(MAX_MATRIX_SIZE*MAX_MATRIX_SIZE) max_read_burst_length=128 max_widen_bitwidth=128 max_write_burst_length=128
#pragma HLS INTERFACE mode=m_axi port=matrix_in_2 bundle=matrix_b depth=(MAX_MATRIX_SIZE*MAX_MATRIX_SIZE) max_read_burst_length=128 max_widen_bitwidth=128 max_write_burst_length=128
#pragma HLS INTERFACE mode=m_axi port=matrix_out bundle=matrix_c depth=(MAX_MATRIX_SIZE*MAX_MATRIX_SIZE) max_read_burst_length=128 max_widen_bitwidth=128 max_write_burst_length=128

    for(ap_uint<17> j=0; j<(size/MATRIX_SIZE)*(size/MATRIX_SIZE); ++j)
    {
    #pragma HLS dataflow
    #pragma HLS LOOP_TRIPCOUNT max=(MAX_MATRIX_SIZE/MATRIX_SIZE * MAX_MATRIX_SIZE/MATRIX_SIZE)
        matrix_out_t Matrix_4x4_final[MATRIX_SIZE][MATRIX_SIZE] = {};
        #pragma HLS ARRAY_PARTITION variable=Matrix_4x4_final dim=0 type=complete
        for(ap_uint<11> i=0; i<(size/MATRIX_SIZE); ++i)
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
