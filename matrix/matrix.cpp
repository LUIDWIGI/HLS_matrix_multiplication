#include "matrix.hpp"

void matrix_mult(matrix_in_t matrix_in_1[MATRIX_SIZE][MATRIX_SIZE],
                 matrix_in_t matrix_in_2[MATRIX_SIZE][MATRIX_SIZE],
                 matrix_out_t matrix_out[MATRIX_SIZE][MATRIX_SIZE]) {
#pragma HLS INTERFACE mode=s_axilite port=matrix_out bundle=matrix_data 
#pragma HLS INTERFACE mode=s_axilite port=matrix_in_1 bundle=matrix_data 
#pragma HLS INTERFACE mode=s_axilite port=matrix_in_2 bundle=matrix_data 
#pragma HLS INTERFACE mode=s_axilite port=return bundle=matrix_data

#pragma HLS array_partition variable=matrix_in_1 complete dim=0
#pragma HLS array_partition variable=matrix_in_2 complete dim=0
#pragma HLS array_partition variable=matrix_out complete dim=0

    for (ap_uint<6> row = 0; row < MATRIX_SIZE; ++row) {
        //#pragma HLS LOOP_FLATTEN ON
        for (ap_uint<6> col = 0; col < MATRIX_SIZE; ++col) {
        // #pragma HLS LOOP_FLATTEN ON
        #pragma HLS PIPELINE II=1
            matrix_out_t sum = 0;
            for (ap_uint<6> k = 0; k < MATRIX_SIZE; ++k) {
                sum += matrix_in_1[row][k] * matrix_in_2[k][col];
            }
            matrix_out[row][col] = sum;
        }
        
    }
}
