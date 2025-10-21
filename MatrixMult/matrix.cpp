#include "MatrixMult.hpp"

void multiplier(matrix_in_t matrix_in_1[MATRIX_SIZE][MATRIX_SIZE],
                 matrix_in_t matrix_in_2[MATRIX_SIZE][MATRIX_SIZE],
                 matrix_out_t matrix_out[MATRIX_SIZE][MATRIX_SIZE]) {

#pragma HLS ARRAY_PARTITION variable=matrix_in_1 dim=0 type=complete
#pragma HLS ARRAY_PARTITION variable=matrix_in_2 dim=0 type=complete
#pragma HLS ARRAY_PARTITION variable=matrix_out dim=0 type=complete

    for (ap_uint<4> row = 0; row < MATRIX_SIZE; ++row) {
        for (ap_uint<4> col = 0; col < MATRIX_SIZE; ++col) {
            matrix_out_t sum = 0;
            for (ap_uint<4> k = 0; k < MATRIX_SIZE; ++k) {
                #pragma HLS pipeline II=1
                sum += matrix_in_1[row][k] * matrix_in_2[k][col];
            }
            matrix_out[row][col] = sum;
        }
        
    }
}
