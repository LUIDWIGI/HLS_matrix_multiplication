#include "MatrixMult.hpp"
#include <cstdint>
#include <iostream>
#include <ostream>

typedef int16_t matrix_in_t;
typedef int16_t matrix_16_t;
typedef int32_t matrix_out_t;
typedef int32_t matrix_32_t;

void bramDownloader(matrix_in_t* input1,
                    matrix_in_t* input2,
                    uint16_t size,
                    matrix_16_t output1[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE],
                    matrix_16_t output2[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE])
{
// #pragma HLS INLINE
#pragma HLS ARRAY_PARTITION variable=output1 dim=1 type=complete
// #pragma HLS BIND_STORAGE variable=output1 type=ram_2p impl=bram
#pragma HLS ARRAY_PARTITION variable=output2 dim=1 type=complete
// #pragma HLS BIND_STORAGE variable=output2 type=ram_2p impl=bram

    std::cout << "output matrix 1:" << std::endl;
    assert(MAX_MATRIX_SIZE % 2 == 0);
    assert(size % 4 == 0);
    for(uint16_t r=0; r<size; ++r)
    {
        #pragma HLS LOOP_TRIPCOUNT max=MAX_MATRIX_SIZE
        for(uint16_t c=0; c<size; ++c)
        {
            #pragma HLS LOOP_TRIPCOUNT max=MAX_MATRIX_SIZE
            output1[r][c] = input1[r*size+c];
            output2[r][c] = input2[r*size+c];
            std::cout << output1[r][c] << " ";
        }
        std::cout << std::endl << std::endl;
    }
}

void MatrixMult(matrix_in_t* matrix_in_1,
                matrix_in_t* matrix_in_2,
                uint16_t size,
                matrix_out_t* matrix_out)
{
#pragma HLS INTERFACE mode=m_axi port=matrix_in_1 bundle=matrix_a depth=(MAX_MATRIX_SIZE*MAX_MATRIX_SIZE) max_read_burst_length=64 max_widen_bitwidth=64
#pragma HLS INTERFACE mode=m_axi port=matrix_in_2 bundle=matrix_b depth=(MAX_MATRIX_SIZE*MAX_MATRIX_SIZE) max_read_burst_length=64 max_widen_bitwidth=64
#pragma HLS INTERFACE mode=m_axi port=matrix_out bundle=matrix_c depth=(MAX_MATRIX_SIZE*MAX_MATRIX_SIZE) max_read_burst_length=64 max_widen_bitwidth=64

// #pragma HLS CACHE port=matrix_in_1 lines=32 depth=64
// #pragma HLS CACHE port=matrix_in_2 lines=32 depth=64

    matrix_16_t matrix1[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
    matrix_16_t matrix2[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];

    bramDownloader(matrix_in_1, matrix_in_2, size, matrix1, matrix2);
 
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


            matrixSlicer(matrix1, matrix2, size, Matrix_4x4_1, Matrix_4x4_2);
            multiplier(Matrix_4x4_1, Matrix_4x4_2, matrix_4x4_out);
            matrixAdder(matrix_4x4_out, Matrix_4x4_final);
        }        
        matrixStitcher(Matrix_4x4_final, size, matrix_out);
    }
}