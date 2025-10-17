#include "MatrixMult.hpp"
#include <iostream>

#define TEST_SIZE 8

void softwareTester(matrix_in_t* input1, matrix_in_t* input2, matrix_out_t* output, uint16_t size)
{
    for (uint16_t i = 0; i < size; ++i) {
        for (uint16_t j = 0; j < size; ++j) {
            output[i * size + j] = 0;
            for (uint16_t k = 0; k < size; ++k) {
                output[i * size + j] += input1[i * size + k] * input2[k * size + j];
            }
        }
    }
}

//####______ defining matrices ______####//
matrix_in_t matrix_1[TEST_SIZE][TEST_SIZE] = {
    {1, 2, 3, 4, 5, 6, 7, 8},
    {9, 10, 11, 12, 13, 14, 15, 16},
    {17, 18, 19, 20, 21, 22, 23, 24},
    {25, 26, 27, 28, 29, 30, 31, 32},
    {33, 34, 35, 36, 37, 38, 39, 40},
    {41, 42, 43, 44, 45, 46, 47, 48},
    {49, 50, 51, 52, 53, 54, 55, 56},
    {57, 58, 59, 60, 61, 62, 63, 64}
};

matrix_in_t matrix_2[TEST_SIZE][TEST_SIZE] = {
    {1, 2, 3, 4, 5, 6, 7, 8},
    {9, 10, 11, 12, 13, 14, 15, 16},
    {17, 18, 19, 20, 21, 22, 23, 24},
    {25, 26, 27, 28, 29, 30, 31, 32},
    {33, 34, 35, 36, 37, 38, 39, 40},
    {41, 42, 43, 44, 45, 46, 47, 48},
    {49, 50, 51, 52, 53, 54, 55, 56},
    {57, 58, 59, 60, 61, 62, 63, 64}
};

    // {1, 2, 3, 4, 5, 6, 7, 8},
    // {9, 10, 11, 12, 13, 14, 15, 16},
    // {17, 18, 19, 20, 21, 22, 23, 24},
    // {25, 26, 27, 28, 29, 30, 31, 32},
    // {33, 34, 35, 36, 37, 38, 39, 40},
    // {41, 42, 43, 44, 45, 46, 47, 48},
    // {49, 50, 51, 52, 53, 54, 55, 56},
    // {57, 58, 59, 60, 61, 62, 63, 64}
// {
//     {65, 66, 67, 68, 69, 70, 71, 72},
//     {73, 74, 75, 76, 77, 78, 79, 80},
//     {81, 82, 83, 84, 85, 86, 87, 88},
//     {89, 90, 91, 92, 93, 94, 95, 96},
//     {97, 98, 99, 100, 101, 102, 103, 104},
//     {105, 106, 107, 108, 109, 110, 111, 112},
//     {113, 114, 115, 116, 117, 118, 119, 120},
//     {121, 122, 123, 124, 125, 126, 127, 128}
// };

matrix_out_t finalMatrix[TEST_SIZE][TEST_SIZE] = {};



//####_______ main function ______####//
int main() {
    
    MatrixMult(&matrix_1[0][0], &matrix_2[0][0], TEST_SIZE, &finalMatrix[0][0]);
    matrix_out_t softwareResult[TEST_SIZE * TEST_SIZE] = {};
    matrix_out_t softwareResult3D[TEST_SIZE][TEST_SIZE] = {};
    softwareTester(&matrix_1[0][0], &matrix_2[0][0], &softwareResult[0], TEST_SIZE);
    for (int i = 0; i < TEST_SIZE; ++i) {
        for (int j = 0; j < TEST_SIZE; ++j) {
            softwareResult3D[i][j] = softwareResult[i * TEST_SIZE + j];
        }
    }

//####________ Printing output ________####//
    std::cout << std::endl;
    std::cout << "Resultant Matrix:" << std::endl;
    for (int i = 0; i < TEST_SIZE; ++i) {
        for (int j = 0; j < TEST_SIZE; ++j) {
            std::cout << finalMatrix[i][j] << " ";
            if (finalMatrix[i][j] != softwareResult3D[i][j]) {
                std::cerr << "Failure at: " << i << ", " << j << std::endl
                << "expected: " << softwareResult3D[i][j] << "   received: " << finalMatrix[i][j] << std::endl;
            }
        }
        std::cout << std::endl;
    }

    return 0;
}

