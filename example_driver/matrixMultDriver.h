#ifndef MATRIX_MULT_DRIVER_H
#define MATRIX_MULT_DRIVER_H

#include "xil_types.h"
#include <xstatus.h>
#include <stdlib.h>

#if __has_include("xmatrixmult.h")
    #include "xmatrixmult.h"
#endif
#if __has_include("xmatrixmult_nocache.h")
    #include "xmatrixmult_nocache.h"
#endif

#ifdef XMATRIXMULT_H

/**
 * @brief Initializes the matrix multiplication hardware accelerator with cache support
 * 
 * @param matrixMultPtr Pointer to the XMatrixmult instance to initialize
 * @param ctrl_baseaddr Base address of the matrix multiplication hardware controller
 * @return int XST_SUCCESS if initialization succeeds, error code otherwise
 */
int init_maxtrix_mult(XMatrixmult *matrixMultPtr, UINTPTR ctrl_baseaddr);

/**
 * @brief Computes matrix multiplication C = A * B using hardware accelerator with cache
 * 
 * This function handles non-square matrices by extending them with zeros to form square
 * matrices (hardware limitation). It configures the hardware accelerator, transfers
 * matrix pointers, starts the computation, and waits for completion.
 * 
 * @param matrixMultPtr Pointer to initialized XMatrixmult instance
 * @param A Pointer to input matrix A (16-bit signed integers)
 * @param B Pointer to input matrix B (16-bit signed integers)
 * @param C Pointer to output matrix C (32-bit signed integers)
 * @param rowsA Number of rows in matrix A
 * @param colsA Number of columns in matrix A
 * @param rowsB Number of rows in matrix B
 * @param colsB Number of columns in matrix B
 * @return int XST_SUCCESS if computation succeeds, XST_FAILURE otherwise
 * 
 * @note For non-square matrices, new memory is allocated. Caller should manage original pointers.
 * @note This function blocks until hardware computation completes.
 */
int compute_matrix(XMatrixmult *matrixMultPtr, s16 *A, s16 *B, s32 *C,
                   u32 rowsA, u32 colsA, u32 rowsB, u32 colsB);

#endif

#ifdef XMATRIXMULT_NOCACHE_H

/**
 * @brief Initializes the matrix multiplication hardware accelerator without cache support
 * 
 * @param matrixMultPtr Pointer to the XMatrixmult_nocache instance to initialize
 * @param ctrl_baseaddr Base address of the matrix multiplication hardware controller
 * @return int XST_SUCCESS if initialization succeeds, error code otherwise
 */
int init_maxtrix_mult_no_cache(XMatrixmult_nocache *matrixMultPtr, UINTPTR ctrl_baseaddr);

/**
 * @brief Computes matrix multiplication C = A * B using hardware accelerator without cache
 * 
 * This function handles non-square matrices by extending them with zeros to form square
 * matrices (hardware limitation). It configures the hardware accelerator, transfers
 * matrix pointers, starts the computation, and waits for completion.
 * 
 * @param matrixMultPtr Pointer to initialized XMatrixmult_nocache instance
 * @param A Pointer to input matrix A (16-bit signed integers)
 * @param B Pointer to input matrix B (16-bit signed integers)
 * @param C Pointer to output matrix C (32-bit signed integers)
 * @param rowsA Number of rows in matrix A
 * @param colsA Number of columns in matrix A
 * @param rowsB Number of rows in matrix B
 * @param colsB Number of columns in matrix B
 * @return int XST_SUCCESS if computation succeeds, XST_FAILURE otherwise
 * 
 * @note For non-square matrices, new memory is allocated. Caller should manage original pointers.
 * @note This function blocks until hardware computation completes.
 */
int compute_matrix_no_cache(XMatrixmult_nocache *matrixMultPtr, s16 *A, s16 *B, s32 *C,
                   u32 rowsA, u32 colsA, u32 rowsB, u32 colsB);

#endif

/**
 * @brief Extends matrices to a square form by padding with zeros
 * 
 * This function allocates new square matrices of size new_size x new_size, copies the
 * original matrix data, and pads the rest with zeros. The original matrices are freed
 * and the pointers are updated to point to the new matrices.
 * 
 * @param matrix_A Pointer to pointer of matrix A (will be updated to new allocation)
 * @param matrix_B Pointer to pointer of matrix B (will be updated to new allocation)
 * @param original_rows_A Original number of rows in matrix A
 * @param original_cols_A Original number of columns in matrix A
 * @param original_rows_B Original number of rows in matrix B
 * @param original_cols_B Original number of columns in matrix B
 * @param new_size The new square dimension (both rows and columns)
 * @return int XST_SUCCESS if extension succeeds, XST_FAILURE if memory allocation fails
 * 
 * @warning This function frees the original matrices. Ensure no other references exist.
 * @note new_size should be >= max(original_rows_A, original_cols_A, original_rows_B, original_cols_B)
 */
int extend_with_zeros(s16 **matrix_A, s16 **matrix_B,
                      u32 original_rows_A, u32 original_cols_A, u32 original_rows_B, u32 original_cols_B,
                      u32 new_size);

/**
 * @brief Computes matrix multiplication C = A * B using software implementation
 * 
 * This function performs standard matrix multiplication using three nested loops.
 * It serves as a reference implementation for verifying hardware accelerator results.
 * 
 * @param A Pointer to input matrix A (16-bit signed integers), row-major order
 * @param B Pointer to input matrix B (16-bit signed integers), row-major order
 * @param C Pointer to output matrix C (32-bit signed integers), row-major order
 * @param rowsA Number of rows in matrix A
 * @param colsA Number of columns in matrix A (must equal rowsB for valid multiplication)
 * @param rowsB Number of rows in matrix B (must equal colsA for valid multiplication)
 * @param colsB Number of columns in matrix B
 * @return int XST_SUCCESS if computation succeeds, XST_FAILURE if dimensions are incompatible
 * 
 * @note Result matrix C must be pre-allocated with size rowsA x colsB
 * @note Complexity: O(rowsA * colsB * colsA)
 */
int software_compute_matrix(s16 *A, s16 *B, s32 *C,
                            u32 rowsA, u32 colsA, u32 rowsB, u32 colsB);
// #endif

#endif //MATRIX_MULT_DRIVER_H
