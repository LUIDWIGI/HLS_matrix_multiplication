/******************************************************************************
* Copyright (C) 2023 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/
/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdint.h>
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include <stdlib.h>
#include <xparameters.h>
#include "matrixMultDriver.h"
#include <xiltimer.h>
#include "clockEnablementDriver.h"
#include "sleep.h"
#include "xil_mem.h"
#include "xil_util.h"

#include "xil_cache.h"

//XMatrixmult_nocache matrixMult_NoCache;
XMatrixmult matrixMult_WithCache;


#if 1
int main()
{
    init_platform();

    // Enable clock outputs of the PS
    enable_fclk(0); // Enable FCLK0

    msleep(1);

    xil_printf("Before init\n");
    //init_maxtrix_mult_no_cache(&matrixMult_NoCache, XPAR_MATRIXMULT_NOCACHE_0_BASEADDR);
    init_maxtrix_mult(&matrixMult_WithCache, XPAR_MATRIXMULT_0_BASEADDR);
    xil_printf("After init\n");

    // Pointers
    s16* matrix_A;
    s16* matrix_B;
    s32* matrix_NC_return;
    s32* matrix_WC_return;
    s32* software_result;

    XTime startHW_NC = 0, endHW_NC = 0, startSW = 0, endSW = 0, startHW_WC = 0, endHW_WC = 0;

    // Matrix dimensions
    u32 size = 4;

    // Allocate memory for matrices
    //matrix_A = (s16*)Xil_Malloc(size * size * sizeof(s16), 64);
    matrix_A = (s16*)malloc(size * size * sizeof(s16));
    matrix_B = (s16*)malloc(size * size * sizeof(s16));
    matrix_NC_return = (s32*)malloc(size * size * sizeof(s32));
    matrix_WC_return = (s32*)malloc(size * size * sizeof(s32));
    software_result = (s32*)malloc(size * size * sizeof(s32));

    // Initialize matrices A and B with some values
    // For simplicity, we use small integers
    // Matrix A
    for (u32 i = 0; i < size; i++) {
        for (u32 j = 0; j < size; j++) {
            matrix_A[i * size + j] = (s16)(i + j);
        }
    }
    // Matrix B
    for (u32 i = 0; i < size; i++) {
        for (u32 j = 0; j < size; j++) {
            matrix_B[i * size + j] = (s16)(i + j);
        }
    }
    Xil_DCacheDisable();
    msleep(1);


    // XTime_GetTime(&startHW_NC);
    // compute_matrix_no_cache(&matrixMult_NoCache, matrix_A, matrix_B, matrix_NC_return,
    //                size, size, size, size);
    // XTime_GetTime(&endHW_NC);
    // double timeHW_NC = 1.0 * (endHW_NC - startHW_NC) / (COUNTS_PER_SECOND);
    // u64 timeHW_millis = (endHW_NC - startHW_NC) * 1000 / COUNTS_PER_SECOND;
    // u64 timeHW_micro = (endHW_NC - startHW_NC) * 1000000 / COUNTS_PER_SECOND;

    // if (timeHW_millis > 100) {
    //     xil_printf("Hardware (without cache) matrix multiplication time: %llu milliseconds\n", timeHW_millis);
    // } else {
    //     xil_printf("Hardware (without cache) matrix multiplication time: %llu microseconds\n", timeHW_micro);
    // }

    XTime_GetTime(&startHW_WC);
    compute_matrix(&matrixMult_WithCache, matrix_A, matrix_B, matrix_WC_return,
                   size, size, size, size);
    XTime_GetTime(&endHW_WC);
    double timeHW_WC = 1.0 * (endHW_WC - startHW_WC) / (COUNTS_PER_SECOND);
    u64 timeHW_WC_millis = (endHW_WC - startHW_WC) * 1000 / COUNTS_PER_SECOND;
    u64 timeHW_WC_micro = (endHW_WC - startHW_WC) * 1000000 / COUNTS_PER_SECOND;
    if (timeHW_WC_millis > 100) {
        xil_printf("Hardware (with cache) matrix multiplication time: %llu milliseconds\n", timeHW_WC_millis);
    } else {
        xil_printf("Hardware (with cache) matrix multiplication time: %llu microseconds\n", timeHW_WC_micro);
    }

    Xil_DCacheEnable();
    msleep(1);

    if (size <= 1024) {
        XTime_GetTime(&startSW);
        software_compute_matrix(matrix_A, matrix_B, software_result,
                                size, size, size, size);
        XTime_GetTime(&endSW);

        double timeSW = 1.0 * (endSW - startSW) / (COUNTS_PER_SECOND);
        u64 timeSW_millis = (endSW - startSW) * 1000 / COUNTS_PER_SECOND;
        u64 timeSW_micro = (endSW - startSW) * 1000000 / COUNTS_PER_SECOND;
        if (timeSW_millis > 100) {
            xil_printf("Software matrix multiplication time: %llu milliseconds\n", timeSW_millis);
        } else {
            xil_printf("Software matrix multiplication time: %llu microseconds\n", timeSW_micro);
        }

        // Print HW speedup compared to software
        xil_printf("Speedup (SW/HW with cache): %llu percent\n", (u64)((timeSW / timeHW_WC)*100));
        //xil_printf("Speedup (SW/HW without cache): %llu percent\n", (u64)((timeSW / timeHW_NC)*100));

        // Verify results
        // for (u32 row = 0; row < size; ++row) {
        //     for (u32 col = 0; col < size; ++col)
        //     if (matrix_NC_return[row*size+col] != software_result[row*size+col]) {
        //         xil_printf("Mismatch at index %u, %u: Hardware (without cache) result = %u, Software result = %u\n",
        //                    row, col, matrix_NC_return[row*size+col], software_result[row*size+col]);
        //         return -1;
        //     }
        // }
        for (u32 row = 0; row < size; ++row) {
            for (u32 col = 0; col < size; ++col)
            if (matrix_WC_return[row*size+col] != software_result[row*size+col]) {
                xil_printf("Mismatch at index %u, %u: Hardware (with cache) result = %u, Software result = %u\n",
                        row, col, matrix_WC_return[row*size+col], software_result[row*size+col]);
                return -1;
            }
        }
    }
    cleanup_platform();
    return 0;
}

#else

#define MAX_MATRIX_SIZE 512

int main()
{
    init_platform();

    // Enable clock outputs of the PS
    enable_fclk(0); // Enable FCLK0

    msleep(1);

    xil_printf("Before init\n");
    //init_maxtrix_mult_no_cache(&matrixMult_NoCache, XPAR_MATRIXMULT_NOCACHE_0_BASEADDR);
    init_maxtrix_mult(&matrixMult_WithCache, XPAR_MATRIXMULT_0_BASEADDR);
    xil_printf("After init\n");

    // Pointers
    s16* matrix_A;
    s16* matrix_B;
    s32* matrix_NC_return;
    s32* matrix_WC_return;
    s32* software_result;

    // Allocate memory for matrices
    matrix_A = (s16*)malloc(MAX_MATRIX_SIZE * MAX_MATRIX_SIZE * sizeof(s16));
    matrix_B = (s16*)malloc(MAX_MATRIX_SIZE * MAX_MATRIX_SIZE * sizeof(s16));
    matrix_NC_return = (s32*)malloc(MAX_MATRIX_SIZE * MAX_MATRIX_SIZE * sizeof(s32));
    matrix_WC_return = (s32*)malloc(MAX_MATRIX_SIZE * MAX_MATRIX_SIZE * sizeof(s32));
    software_result = (s32*)malloc(MAX_MATRIX_SIZE * MAX_MATRIX_SIZE * sizeof(s32));

    if (matrix_A == NULL || matrix_B == NULL || matrix_NC_return == NULL ||
        matrix_WC_return == NULL || software_result == NULL) {
        xil_printf("Memory allocation failed!\n");
        return -1;
    }

    u32 testSizeArray[] = {4, 16, 32, 64, 128, 256};

    for (unsigned int testCases = 0; testCases < (sizeof(testSizeArray)/sizeof(u32)); testCases++) {
        u32 size = testSizeArray[testCases];
        xil_printf("Starting test for matrix size: %u x %u\n", size, size);

        XTime startHW_NC = 0, endHW_NC = 0, startSW = 0, endSW = 0, startHW_WC = 0, endHW_WC = 0;


        xil_printf("Filling matrices\n");
        // Initialize matrices A and B with some values
        // For simplicity, we use small integers
        // Matrix A
        for (u32 i = 0; i < size; i++) {
            for (u32 j = 0; j < size; j++) {
                matrix_A[i * size + j] = (s16)((i + j) % 256);
            }
        }
        // Matrix B
        for (u32 i = 0; i < size; i++) {
            for (u32 j = 0; j < size; j++) {
                matrix_B[i * size + j] = (s16)((i + j) % 256);
            }
        }

        xil_printf("Computing matrices in hardware\n");
        Xil_DCacheDisable();
        msleep(1);


        // XTime_GetTime(&startHW_NC);
        // compute_matrix_no_cache(&matrixMult_NoCache, matrix_A, matrix_B, matrix_NC_return,
        //                size, size, size, size);
        // XTime_GetTime(&endHW_NC);
        // double timeHW_NC = 1.0 * (endHW_NC - startHW_NC) / (COUNTS_PER_SECOND);
        // u64 timeHW_millis = (endHW_NC - startHW_NC) * 1000 / COUNTS_PER_SECOND;
        // u64 timeHW_micro = (endHW_NC - startHW_NC) * 1000000 / COUNTS_PER_SECOND;

        // if (timeHW_millis > 100) {
        //     xil_printf("Hardware (without cache) matrix multiplication time: %llu milliseconds\n", timeHW_millis);
        // } else {
        //     xil_printf("Hardware (without cache) matrix multiplication time: %llu microseconds\n", timeHW_micro);
        // }

        XTime_GetTime(&startHW_WC);
        compute_matrix(&matrixMult_WithCache, matrix_A, matrix_B, matrix_WC_return,
                    size, size, size, size);
        XTime_GetTime(&endHW_WC);
        double timeHW_WC = 1.0 * (endHW_WC - startHW_WC) / (COUNTS_PER_SECOND);
        u64 timeHW_WC_millis = (endHW_WC - startHW_WC) * 1000 / COUNTS_PER_SECOND;
        u64 timeHW_WC_micro = (endHW_WC - startHW_WC) * 1000000 / COUNTS_PER_SECOND;
        if (timeHW_WC_millis > 100) {
            xil_printf("Hardware (with cache) matrix multiplication time: %llu milliseconds\n", timeHW_WC_millis);
        } else {
            xil_printf("Hardware (with cache) matrix multiplication time: %llu microseconds\n", timeHW_WC_micro);
        }

        Xil_DCacheEnable();
        msleep(1);

        if (size <= 128) {
            xil_printf("Computing matrices in software\n");

            XTime_GetTime(&startSW);
            software_compute_matrix(matrix_A, matrix_B, software_result,
                                    size, size, size, size);
            XTime_GetTime(&endSW);

            double timeSW = 1.0 * (endSW - startSW) / (COUNTS_PER_SECOND);
            u64 timeSW_millis = (endSW - startSW) * 1000 / COUNTS_PER_SECOND;
            u64 timeSW_micro = (endSW - startSW) * 1000000 / COUNTS_PER_SECOND;
            if (timeSW_millis > 100) {
                xil_printf("Software matrix multiplication time: %llu milliseconds\n", timeSW_millis);
            } else {
                xil_printf("Software matrix multiplication time: %llu microseconds\n", timeSW_micro);
            }

            // Print HW speedup compared to software
            xil_printf("Speedup (SW/HW with cache): %llu percent\n", (u64)((timeSW / timeHW_WC)*100));
            //xil_printf("Speedup (SW/HW without cache): %llu percent\n", (u64)((timeSW / timeHW_NC)*100));

            // Verify results
            // for (u32 row = 0; row < size; ++row) {
            //     for (u32 col = 0; col < size; ++col)
            //     if (matrix_NC_return[row*size+col] != software_result[row*size+col]) {
            //         xil_printf("Mismatch at index %u, %u: Hardware (without cache) result = %u, Software result = %u\n",
            //                    row, col, matrix_NC_return[row*size+col], software_result[row*size+col]);
            //         return -1;
            //     }
            // }
            xil_printf("Verifying results\n");
            for (u32 row = 0; row < size; ++row) {
                for (u32 col = 0; col < size; ++col)
                if (matrix_WC_return[row*size+col] != software_result[row*size+col]) {
                    xil_printf("Mismatch at index %u, %u: Hardware (with cache) result = %u, Software result = %u\n",
                            row, col, matrix_WC_return[row*size+col], software_result[row*size+col]);
                    return -1;
                }
            }
        }
    }
    cleanup_platform();
    return 0;
}

#endif
