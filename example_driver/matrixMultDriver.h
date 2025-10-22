#ifndef MATRIX_MULT_DRIVER_H
#define MATRIX_MULT_DRIVER_H

#include "xmatrixmult.h"
#include "xil_types.h"
#include <xmatrixmult.h>
#include <xstatus.h>
#include <stdlib.h>

int init_maxtrix_mult(XMatrixmult *matrixMultPtr, UINTPTR ctrl_baseaddr);

int compute_matrix(XMatrixmult *matrixMultPtr, s16 *A, s16 *B, s32 *C,
                   u32 rowsA, u32 colsA, u32 rowsB, u32 colsB);

int extend_with_zeros(s16 **matrix_A, s16 **matrix_B,
                      u32 original_rows_A, u32 original_cols_A, u32 original_rows_B, u32 original_cols_B,
                      u32 new_size);

int software_compute_matrix(s16 *A, s16 *B, s32 *C,
                            u32 rowsA, u32 colsA, u32 rowsB, u32 colsB);

#endif //MATRIX_MULT_DRIVER_H
