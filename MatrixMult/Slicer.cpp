#include "MatrixMult.hpp"
#include <cstdint>

void matrixSlicer(matrix_in_t* matrix_in_1,
                 matrix_in_t* matrix_in_2,
                 uint32_t size,
                 matrix_16_t matrix_out_1[MATRIX_SIZE][MATRIX_SIZE],
                 matrix_16_t matrix_out_2[MATRIX_SIZE][MATRIX_SIZE]) {
#pragma HLS INLINE
#pragma HLS ARRAY_PARTITION variable=matrix_out_2 dim=0 type=complete
#pragma HLS ARRAY_PARTITION variable=matrix_out_1 dim=0 type=complete

// #pragma HLS INTERFACE mode=ap_hs port=matrix_out_1
// #pragma HLS INTERFACE mode=ap_hs port=matrix_out_2
// #pragma HLS INTERFACE mode=s_axilite port=return bundle=matrix_data

static uint16_t arow = 0;
static uint16_t acol = 0;
static uint16_t acount = 0;
static uint16_t brow = 0;
static uint16_t bcol = 0;
static uint16_t counter = 0;

    for (uint16_t row=0; row<MATRIX_SIZE; ++row)
    {
        for (uint16_t col=0; col<MATRIX_SIZE; ++col)
        {
            #pragma HLS PIPELINE II=2
            matrix_out_1[row][col] = matrix_in_1[(row+arow)*MAX_MATRIX_SIZE + (col+acol)];
            matrix_out_2[row][col] = matrix_in_2[(row+brow)*MAX_MATRIX_SIZE + (col+bcol)];
        }
    }

    acol += MATRIX_SIZE;
    brow += MATRIX_SIZE;
    if (acol >= size) {
        acol = 0;
        brow = 0;
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
