#include "matrixMultDriver.h"

#ifdef XMATRIXMULT_H

int init_maxtrix_mult(XMatrixmult *matrixMultPtr, UINTPTR ctrl_baseaddr) {
  int status;
  status = XMatrixmult_Initialize(matrixMultPtr, ctrl_baseaddr);
  if (status != XST_SUCCESS) {
    return status;
  }

  //XMatrixmult_DisableAutoRestart(matrixMultPtr);
  return XST_SUCCESS;
}

int compute_matrix(XMatrixmult *matrixMultPtr, s16 *A, s16 *B, s32 *C,
                   u32 rowsA, u32 colsA, u32 rowsB, u32 colsB) {

    int status;

    // Make sure both matrices are square (fill others with zeros if needed)
    // This is a hardware limitation for this example
    u32 new_size = 0;
    if (rowsA != colsA || rowsB != colsB || colsA != rowsB) {
        if (rowsA > new_size) {
            new_size = rowsA;
        }
        if (colsA > new_size) {
            new_size = colsA;
        }
        if (rowsB > new_size) {
            new_size = rowsB;
        }
        if (colsB > new_size) {
            new_size = colsB;
        }
        status = extend_with_zeros(&A, &B,
                                   rowsA, colsA,
                                   rowsB, colsB, new_size);
        if (status != XST_SUCCESS) {
            xil_printf("Failed to extend matrices to square form.\n");
            return status;
        }
        XMatrixmult_Set_size(matrixMultPtr, new_size);

    } else {
        new_size = rowsA; // or colsA, rowsB, colsB (all are equal)
        XMatrixmult_Set_size(matrixMultPtr, new_size);
    }
    u32 actual_value = XMatrixmult_Get_size(matrixMultPtr);
    if (actual_value != new_size) {
        xil_printf("Failed to set matrix size. Expected: %u, received %u", new_size,
                   actual_value);
        return XST_FAILURE;
    }

    XMatrixmult_Set_matrix_in_1(matrixMultPtr, (u64)(uintptr_t)A);
    XMatrixmult_Set_matrix_in_2(matrixMultPtr, (u64)(uintptr_t)B);
    XMatrixmult_Set_matrix_out(matrixMultPtr, (u64)(uintptr_t)C);

    XMatrixmult_Start(matrixMultPtr);

    while (!XMatrixmult_IsDone(matrixMultPtr));

    return XST_SUCCESS;
}

#endif

#ifdef XMATRIXMULT_NOCACHE_H

int init_maxtrix_mult_no_cache(XMatrixmult_nocache *matrixMultPtr, UINTPTR ctrl_baseaddr) {
  int status;
  status = XMatrixmult_nocache_Initialize(matrixMultPtr, ctrl_baseaddr);
  if (status != XST_SUCCESS) {
    return status;
  }

  //XMatrixmult_DisableAutoRestart(matrixMultPtr);
  return XST_SUCCESS;
}

int compute_matrix_no_cache(XMatrixmult_nocache *matrixMultPtr, s16 *A, s16 *B, s32 *C,
                   u32 rowsA, u32 colsA, u32 rowsB, u32 colsB) {

    int status;

    // Make sure both matrices are square (fill others with zeros if needed)
    // This is a hardware limitation for this example
    u32 new_size = 0;
    if (rowsA != colsA || rowsB != colsB || colsA != rowsB) {
        if (rowsA > new_size) {
            new_size = rowsA;
        }
        if (colsA > new_size) {
            new_size = colsA;
        }
        if (rowsB > new_size) {
            new_size = rowsB;
        }
        if (colsB > new_size) {
            new_size = colsB;
        }
        status = extend_with_zeros(&A, &B,
                                   rowsA, colsA,
                                   rowsB, colsB, new_size);
        if (status != XST_SUCCESS) {
            xil_printf("Failed to extend matrices to square form.\n");
            return status;
        }
        XMatrixmult_nocache_Set_size(matrixMultPtr, new_size);

    } else {
        new_size = rowsA; // or colsA, rowsB, colsB (all are equal)
        XMatrixmult_nocache_Set_size(matrixMultPtr, new_size);
    }
    u32 actual_value = XMatrixmult_nocache_Get_size(matrixMultPtr);
    if (actual_value != new_size) {
        xil_printf("Failed to set matrix size. Expected: %u, received %u", new_size,
                   actual_value);
        return XST_FAILURE;
    }

    XMatrixmult_nocache_Set_matrix_in_1(matrixMultPtr, (u64)(uintptr_t)A);
    XMatrixmult_nocache_Set_matrix_in_2(matrixMultPtr, (u64)(uintptr_t)B);
    XMatrixmult_nocache_Set_matrix_out(matrixMultPtr, (u64)(uintptr_t)C);

    XMatrixmult_nocache_Start(matrixMultPtr);

    while (!XMatrixmult_nocache_IsDone(matrixMultPtr));

    return XST_SUCCESS;
}

#endif

int extend_with_zeros(s16 **matrix_A, s16 **matrix_B, u32 original_rows_A,
                      u32 original_cols_A, u32 original_rows_B,
                      u32 original_cols_B, u32 new_size) {

    // Allocate new arrays on the heap with size new_size x new_size
    s16 *new_A = (s16 *)malloc(new_size * new_size * sizeof(s16));
    s16 *new_B = (s16 *)malloc(new_size * new_size * sizeof(s16));

    if (new_A == NULL || new_B == NULL) {
        // Allocation failed
        if (new_A != NULL) free(new_A);
        if (new_B != NULL) free(new_B);
        return XST_FAILURE;
    }

    // Initialize new arrays with zeros
    for (u32 i = 0; i < new_size * new_size; i++) {
        new_A[i] = 0;
        new_B[i] = 0;
    }

    // Copy original matrix A data
    for (u32 i = 0; i < original_rows_A; i++) {
        for (u32 j = 0; j < original_cols_A; j++) {
        new_A[i * new_size + j] = (*matrix_A)[i * original_cols_A + j];
        }
    }

    // Copy original matrix B data
    for (u32 i = 0; i < original_rows_B; i++) {
        for (u32 j = 0; j < original_cols_B; j++) {
        new_B[i * new_size + j] = (*matrix_B)[i * original_cols_B + j];
        }
    }

    // Free old arrays and update pointers
    free(*matrix_A);
    free(*matrix_B);
    *matrix_A = new_A;
    *matrix_B = new_B;

    return XST_SUCCESS;
}

int software_compute_matrix(s16 *A, s16 *B, s32 *C,
                             u32 rowsA, u32 colsA, u32 rowsB, u32 colsB) {
    if (colsA != rowsB) {
        return XST_FAILURE; // Incompatible dimensions
    }

    for (u32 i = 0; i < rowsA; i++) {
        for (u32 j = 0; j < colsB; j++) {
            C[i * colsB + j] = 0;
            for (u32 k = 0; k < colsA; k++) {
                C[i * colsB + j] += A[i * colsA + k] * B[k * colsB + j];
            }
        }
    }

    return XST_SUCCESS;
}
