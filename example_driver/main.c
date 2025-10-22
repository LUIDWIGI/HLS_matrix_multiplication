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

XMatrixmult matrixMultPtr;

int main()
{
    init_platform();

    // Enable clock outputs of the PS
    enable_fclk(0); // Enable FCLK0

    msleep(1);

    xil_printf("Before init\n");
    init_maxtrix_mult(&matrixMultPtr, XPAR_XMATRIXMULT_0_BASEADDR);
    xil_printf("After init\n");

    // Pointers
    s16* matrix_A;
    s16* matrix_B;
    s32* matrix_C;
    s32* software_result;

    XTime startHW = 0, endHW = 0, startSW = 0, endSW = 0;

    // Matrix dimensions
    u32 size = 128;

    // Allocate memory for matrices
    //matrix_A = (s16*)Xil_Malloc(size * size * sizeof(s16), 64);
    matrix_A = (s16*)malloc(size * size * sizeof(s16));
    matrix_B = (s16*)malloc(size * size * sizeof(s16));
    matrix_C = (s32*)malloc(size * size * sizeof(s32));
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
            matrix_B[i * size + j] = (s16)(i * j);
        }
    }
    Xil_DCacheDisable();
    msleep(1);


    XTime_GetTime(&startHW);
    compute_matrix(&matrixMultPtr, matrix_A, matrix_B, matrix_C,
                   size, size, size, size);
    XTime_GetTime(&endHW);
    double timeHW = 1.0 * (endHW - startHW) / (COUNTS_PER_SECOND);
    u64 timeHW_millis = (endHW - startHW) * 1000 / COUNTS_PER_SECOND;
    xil_printf("Hardware matrix multiplication time: %llu seconds\n", timeHW_millis);

    Xil_DCacheEnable();
    msleep(1);

    XTime_GetTime(&startSW);
    software_compute_matrix(matrix_A, matrix_B, software_result,
                            size, size, size, size);
    XTime_GetTime(&endSW);

    double timeSW = 1.0 * (endSW - startSW) / (COUNTS_PER_SECOND);
    u64 timeSW_millis = (endSW - startSW) * 1000 / COUNTS_PER_SECOND;
    xil_printf("Software matrix multiplication time: %llu seconds\n", timeSW_millis);

    // Print HW speedup compared to software
    xil_printf("Speedup (SW/HW): %llu percent\n", (u64)((timeSW / timeHW)*100));

    // Verify results
    for (u32 row = 0; row < size; ++row) {
        for (u32 col = 0; col < size; ++col)
        if (matrix_C[row*size+col] != software_result[row*size+col]) {
            xil_printf("Mismatch at index %u, %u: Hardware result = %u, Software result = %u\n",
                       row, col, matrix_C[row*size+col], software_result[row*size+col]);
            return -1;
        }
    }
    cleanup_platform();
    return 0;
}

// int main()
// {
//     init_platform();

//     xil_printf("=== AXI Communication Test ===\r\n");

//     // Enable clock
//     enable_fclk(0);
//     usleep(1000);

//     xil_printf("FCLK0 enabled\r\n");

//     // Test 1: Try to read from the matrix mult base address
//     xil_printf("Attempting direct AXI read from 0x%08X...\r\n",
//                XPAR_XMATRIXMULT_0_BASEADDR);

//     u32 test_val = Xil_In32(XPAR_XMATRIXMULT_0_BASEADDR);

//     xil_printf("SUCCESS! Read value: 0x%08X\r\n", test_val);

//     // Test 2: Try a write (to a safe register like control register)
//     xil_printf("Attempting direct AXI write...\r\n");
//     Xil_Out32(XPAR_XMATRIXMULT_0_BASEADDR, 0x00000000);
//     xil_printf("Write successful!\r\n");

//     // Now try the init
//     xil_printf("\r\nNow trying init function...\r\n");
//     init_maxtrix_mult(&matrixMultPtr, XPAR_XMATRIXMULT_0_BASEADDR);
//     xil_printf("Init successful!\r\n");

//     cleanup_platform();
//     return 0;
// }
