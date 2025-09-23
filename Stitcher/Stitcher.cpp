#include "Slicer.hpp"
#include <cstdint>
#include <iostream>

void matrixSlicer(matrix_in_t* matrix_in_1,
                 matrix_in_t* matrix_in_2,
                 uint32_t size,
                 matrix_out_t matrix_out_1[MATRIX_SIZE][MATRIX_SIZE],
                 matrix_out_t matrix_out_2[MATRIX_SIZE][MATRIX_SIZE]) {
#pragma HLS INTERFACE mode=ap_hs port=matrix_out_1
#pragma HLS INTERFACE mode=ap_hs port=matrix_out_2
#pragma HLS INTERFACE mode=s_axilite port=return bundle=matrix_data

    for (uint16_t i=0; i<size; i+=4)
    {
        for (uint16_t j=0; j<size; j+=4)
        {
            for (uint16_t row=0; row<MATRIX_SIZE; ++row)
            {
                for (uint16_t col=0; col<MATRIX_SIZE; ++col)
                {
                    matrix_out_1[row][col] = matrix_in_1[(row+i)*size + (col+j)];
                    matrix_out_2[row][col] = matrix_in_2[(row+i)*size + (col+j)];
                }
            }

            #ifndef __SYNTHESIS__
                std::cout << "Resultant Matrix " << (i+j)/4 << ":" << std::endl;
                
                for (int i = 0; i < MATRIX_SIZE; ++i) {
                    for (int j = 0; j < MATRIX_SIZE; ++j) {
                        std::cout << matrix_out_1[i][j] << " ";
                        // if (matrix_out_1[i][j] != matrix_expected_1[i][j]) {
                        //     std::cerr << "Failure at: " << i << ", " << j << std::endl
                        //     << "expected: " << matrix_expected_1[i][j] << "received: " << matrix_out_1[i][j] << std::endl;
                        // }
                    }
                    std::cout << std::endl;
                }
            #endif
        }
    }
}
