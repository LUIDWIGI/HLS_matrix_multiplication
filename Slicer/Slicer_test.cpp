#include "Slicer.hpp"
#include <iostream>

#define TEST_SIZE 12

void matrixSlicer(matrix_in_t* matrix_in_1,
                 matrix_in_t* matrix_in_2,
                 uint32_t size,
                 matrix_out_t matrix_out_1[MATRIX_SIZE][MATRIX_SIZE],
                 matrix_out_t matrix_out_2[MATRIX_SIZE][MATRIX_SIZE]);

// Helper function to verify a submatrix has all the same expected value
bool verifySubmatrix(const matrix_out_t matrix[MATRIX_SIZE][MATRIX_SIZE],
                     matrix_out_t expected_value,
                     int& fail_row, int& fail_col) {
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            if (matrix[i][j] != expected_value) {
                fail_row = i;
                fail_col = j;
                return false;
            }
        }
    }
    return true;
}

int main() {
    // 12x12 matrix divided into 9 quadrants (3x3 grid of 4x4 blocks), numbered 1-9
    matrix_in_t matrix_1[TEST_SIZE][TEST_SIZE] = {
        { 1,  1,  1,  1,  2,  2,  2,  2,  3,  3,  3,  3},
        { 1,  1,  1,  1,  2,  2,  2,  2,  3,  3,  3,  3},
        { 1,  1,  1,  1,  2,  2,  2,  2,  3,  3,  3,  3},
        { 1,  1,  1,  1,  2,  2,  2,  2,  3,  3,  3,  3},
        { 4,  4,  4,  4,  5,  5,  5,  5,  6,  6,  6,  6},
        { 4,  4,  4,  4,  5,  5,  5,  5,  6,  6,  6,  6},
        { 4,  4,  4,  4,  5,  5,  5,  5,  6,  6,  6,  6},
        { 4,  4,  4,  4,  5,  5,  5,  5,  6,  6,  6,  6},
        { 7,  7,  7,  7,  8,  8,  8,  8,  9,  9,  9,  9},
        { 7,  7,  7,  7,  8,  8,  8,  8,  9,  9,  9,  9},
        { 7,  7,  7,  7,  8,  8,  8,  8,  9,  9,  9,  9},
        { 7,  7,  7,  7,  8,  8,  8,  8,  9,  9,  9,  9}
    };

    matrix_in_t matrix_2[TEST_SIZE][TEST_SIZE] = {
        { 1,  1,  1,  1,  2,  2,  2,  2,  3,  3,  3,  3},
        { 1,  1,  1,  1,  2,  2,  2,  2,  3,  3,  3,  3},
        { 1,  1,  1,  1,  2,  2,  2,  2,  3,  3,  3,  3},
        { 1,  1,  1,  1,  2,  2,  2,  2,  3,  3,  3,  3},
        { 4,  4,  4,  4,  5,  5,  5,  5,  6,  6,  6,  6},
        { 4,  4,  4,  4,  5,  5,  5,  5,  6,  6,  6,  6},
        { 4,  4,  4,  4,  5,  5,  5,  5,  6,  6,  6,  6},
        { 4,  4,  4,  4,  5,  5,  5,  5,  6,  6,  6,  6},
        { 7,  7,  7,  7,  8,  8,  8,  8,  9,  9,  9,  9},
        { 7,  7,  7,  7,  8,  8,  8,  8,  9,  9,  9,  9},
        { 7,  7,  7,  7,  8,  8,  8,  8,  9,  9,  9,  9},
        { 7,  7,  7,  7,  8,  8,  8,  8,  9,  9,  9,  9}
    };

    // Trace the slicer algorithm:
    // Matrix 1 (acol moves): starts at row 0, scans horizontally: 1, 2, 3
    // Matrix 2 (brow moves): starts at col 0, scans vertically: 1, 4, 7
    // After 3 iterations, Matrix 2 moves to col 1 (bcol=4), Matrix 1 still row 0
    // Matrix 1 continues: 1, 2, 3
    // Matrix 2 continues: 2, 5, 8
    // After 3 more, Matrix 2 moves to col 2 (bcol=8), Matrix 1 still row 0
    // Matrix 1 continues: 1, 2, 3
    // Matrix 2 continues: 3, 6, 9
    // After 9 total, Matrix 1 moves to row 1 (arow=4), Matrix 2 resets to col 0
    // And the pattern repeats...

    // Expected sequence for 12x12:
    // [0]: M1=(0,0)=1, M2=(0,0)=1
    // [1]: M1=(0,4)=2, M2=(4,0)=4
    // [2]: M1=(0,8)=3, M2=(8,0)=7
    // [3]: M1=(0,0)=1, M2=(0,4)=2
    // [4]: M1=(0,4)=2, M2=(4,4)=5
    // [5]: M1=(0,8)=3, M2=(8,4)=8
    // [6]: M1=(0,0)=1, M2=(0,8)=3
    // [7]: M1=(0,4)=2, M2=(4,8)=6
    // [8]: M1=(0,8)=3, M2=(8,8)=9
    // [9]: M1=(4,0)=4, M2=(0,0)=1
    // [10]: M1=(4,4)=5, M2=(4,0)=4
    // [11]: M1=(4,8)=6, M2=(8,0)=7
    // [12]: M1=(4,0)=4, M2=(0,4)=2
    // [13]: M1=(4,4)=5, M2=(4,4)=5
    // [14]: M1=(4,8)=6, M2=(8,4)=8
    // [15]: M1=(4,0)=4, M2=(0,8)=3
    // [16]: M1=(4,4)=5, M2=(4,8)=6
    // [17]: M1=(4,8)=6, M2=(8,8)=9
    // [18]: M1=(8,0)=7, M2=(0,0)=1
    // [19]: M1=(8,4)=8, M2=(4,0)=4
    // [20]: M1=(8,8)=9, M2=(8,0)=7
    // [21]: M1=(8,0)=7, M2=(0,4)=2
    // [22]: M1=(8,4)=8, M2=(4,4)=5
    // [23]: M1=(8,8)=9, M2=(8,4)=8
    // [24]: M1=(8,0)=7, M2=(0,8)=3
    // [25]: M1=(8,4)=8, M2=(4,8)=6
    // [26]: M1=(8,8)=9, M2=(8,8)=9

    struct ExpectedPair {
        matrix_out_t m1;
        matrix_out_t m2;
    };

    ExpectedPair expected_sequence[27] = {
        {1,1}, {2,4}, {3,7},  // M1 row 0, M2 col 0
        {1,2}, {2,5}, {3,8},  // M1 row 0, M2 col 1
        {1,3}, {2,6}, {3,9},  // M1 row 0, M2 col 2
        {4,1}, {5,4}, {6,7},  // M1 row 1, M2 col 0
        {4,2}, {5,5}, {6,8},  // M1 row 1, M2 col 1
        {4,3}, {5,6}, {6,9},  // M1 row 1, M2 col 2
        {7,1}, {8,4}, {9,7},  // M1 row 2, M2 col 0
        {7,2}, {8,5}, {9,8},  // M1 row 2, M2 col 1
        {7,3}, {8,6}, {9,9}   // M1 row 2, M2 col 2
    };

    // zero-initialize output so unused elements are defined
    matrix_out_t matrix_out_1[MATRIX_SIZE][MATRIX_SIZE] = {};
    matrix_out_t matrix_out_2[MATRIX_SIZE][MATRIX_SIZE] = {};

    // Calculate number of 4x4 submatrices: (12/4)^2 = 9
    int num_iterations = ((TEST_SIZE / MATRIX_SIZE) * (TEST_SIZE / MATRIX_SIZE) * (TEST_SIZE / MATRIX_SIZE));

    int passed = 0;
    int failed = 0;

    for (int iter = 0; iter < num_iterations; iter++) {
        std::cout << "\n=== Iteration " << (iter + 1) << "/" << num_iterations << " ===" << std::endl;

        matrixSlicer(&matrix_1[0][0], &matrix_2[0][0], TEST_SIZE, matrix_out_1, matrix_out_2);

        matrix_out_t expected_m1 = expected_sequence[iter].m1;
        matrix_out_t expected_m2 = expected_sequence[iter].m2;
        int fail_row, fail_col;

        std::cout << "Expected Matrix 1: " << expected_m1 << ", Matrix 2: " << expected_m2 << std::endl;

        bool result_m1 = verifySubmatrix(matrix_out_1, expected_m1, fail_row, fail_col);
        bool result_m2 = verifySubmatrix(matrix_out_2, expected_m2, fail_row, fail_col);

        if (result_m1 && result_m2) {
            std::cout << "✓ PASS - Both matrices correct" << std::endl;
            passed++;
        } else {
            std::cout << "✗ FAIL" << std::endl;
            if (!result_m1) {
                std::cout << "  Matrix 1 mismatch at [" << fail_row << "][" << fail_col << "]" << std::endl;
                std::cout << "    Expected: " << expected_m1 << ", Got: " << matrix_out_1[fail_row][fail_col] << std::endl;
            }
            if (!result_m2) {
                std::cout << "  Matrix 2 mismatch at [" << fail_row << "][" << fail_col << "]" << std::endl;
                std::cout << "    Expected: " << expected_m2 << ", Got: " << matrix_out_2[fail_row][fail_col] << std::endl;
            }
            failed++;
        }

        // Print the actual matrices for visual verification
        std::cout << "Matrix 1:" << std::endl;
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            for (int j = 0; j < MATRIX_SIZE; ++j) {
                std::cout << matrix_out_1[i][j] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "Matrix 2:" << std::endl;
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            for (int j = 0; j < MATRIX_SIZE; ++j) {
                std::cout << matrix_out_2[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "Test Results: " << passed << " passed, " << failed << " failed" << std::endl;
    std::cout << "========================================" << std::endl;

    return (failed == 0) ? 0 : 1;
}

