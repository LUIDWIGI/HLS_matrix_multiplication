#include "MatrixMult.hpp"
#include <cstdint>

void matrixSlicer(matrix_in_t* matrix_in_1,
                 matrix_in_t* matrix_in_2,
                 uint32_t size,
                 matrix_16_t matrix_out_1[MATRIX_SIZE][MATRIX_SIZE],
                 matrix_16_t matrix_out_2[MATRIX_SIZE][MATRIX_SIZE]) {
//#pragma HLS INLINE
#pragma HLS pipeline
#pragma HLS ARRAY_PARTITION variable=matrix_out_2 dim=0 type=complete
#pragma HLS ARRAY_PARTITION variable=matrix_out_1 dim=0 type=complete

// #pragma HLS INTERFACE mode=ap_hs port=matrix_out_1
// #pragma HLS INTERFACE mode=ap_hs port=matrix_out_2
// #pragma HLS INTERFACE mode=s_axilite port=return bundle=matrix_data

static ap_uint<13> arow = 0;
static ap_uint<13> offset_a = 0;
static ap_uint<13> bcol = 0;

    for (ap_uint<4> row=0; row<MATRIX_SIZE; ++row)
    {
        #pragma HLS LOOP_flatten
        for (ap_uint<4> col=0; col<MATRIX_SIZE; ++col)
        {
            matrix_out_1[row][col] = matrix_in_1[(row+arow)*size + (col+offset_a)];
            matrix_out_2[row][col] = matrix_in_2[(row+offset_a)*size + (col+bcol)];
        }
    }

    offset_a += MATRIX_SIZE;
    if (offset_a >= size) {
        offset_a = 0;
        bcol += MATRIX_SIZE;
        if (bcol >= size) {
            bcol = 0;
            arow += MATRIX_SIZE;
            if (arow >= size) {
                arow = 0;
            }
        }
    }
}
