#include "Slicer.hpp"
#include <cstdint>

void matrixSlicer(matrix_in_t* matrix_in_1,
                 matrix_in_t* matrix_in_2,
                 uint32_t size,
                 matrix_out_t matrix_out_1[MATRIX_SIZE][MATRIX_SIZE],
                 matrix_out_t matrix_out_2[MATRIX_SIZE][MATRIX_SIZE]) {
#pragma HLS INTERFACE mode=ap_hs port=matrix_out_1
#pragma HLS INTERFACE mode=ap_hs port=matrix_out_2
#pragma HLS INTERFACE mode=s_axilite port=return bundle=matrix_data

    for (int i=0; i<size; ++i)
    {
        int j=0;
        for (int row=0+4*i; row<MATRIX_SIZE+4*i; ++row, ++j)
        {
            for (int col=0+4*j; col<MATRIX_SIZE+4*j; ++col)
            {

            }
        }
    }
}
