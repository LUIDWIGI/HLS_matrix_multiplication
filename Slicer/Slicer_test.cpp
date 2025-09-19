#include "matrix.hpp"
#include <iostream>

void matrix_mult(matrix_in_t matrix_in_1[MATRIX_SIZE][MATRIX_SIZE],
                 matrix_in_t matrix_in_2[MATRIX_SIZE][MATRIX_SIZE],
                 matrix_out_t matrix_out[MATRIX_SIZE][MATRIX_SIZE]);

void expected_result_calc(matrix_in_t matrix_in_1[MATRIX_SIZE][MATRIX_SIZE],
                 matrix_in_t matrix_in_2[MATRIX_SIZE][MATRIX_SIZE],
                 matrix_out_t matrix_out[MATRIX_SIZE][MATRIX_SIZE]) {

    for (int row = 0; row < MATRIX_SIZE; ++row) {
        for (int col = 0; col < MATRIX_SIZE; ++col) {
            matrix_out[row][col] = 0;
            for (int k = 0; k < MATRIX_SIZE; ++k) {
                matrix_out[row][col] += matrix_in_1[row][k] * matrix_in_2[k][col];
            }
        }
    }
}

int main() {
    matrix_in_t matrix_1[MATRIX_SIZE][MATRIX_SIZE] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    matrix_in_t matrix_2[MATRIX_SIZE][MATRIX_SIZE] = {
        {16, 15, 14, 13},
        {12, 11, 10, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    };

    // zero-initialize output so unused elements are defined
    matrix_out_t matrix_out[MATRIX_SIZE][MATRIX_SIZE] = {};

    matrix_out_t matrix_expected[MATRIX_SIZE][MATRIX_SIZE] = {};

    expected_result_calc(matrix_1, matrix_2, matrix_expected);

    matrix_mult(matrix_1, matrix_2, matrix_out);

    std::cout << "Resultant Matrix:" << std::endl;
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            std::cout << matrix_out[i][j] << " ";
            if (matrix_out[i][j] != matrix_expected[i][j]) {
                std::cerr << "Failure at: " << i << ", " << j << std::endl
                << "expected: " << matrix_expected[i][j] << "received: " << matrix_out[i][j] << std::endl;
            }
        }
        std::cout << std::endl;
    }

    return 0;
}

