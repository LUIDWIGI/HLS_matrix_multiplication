// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
// Tool Version Limit: 2025.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XMATRIXMULT_H
#define XMATRIXMULT_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xmatrixmult_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
#ifdef SDT
    char *Name;
#else
    u16 DeviceId;
#endif
    u64 Ctrl_BaseAddress;
} XMatrixmult_Config;
#endif

typedef struct {
    u64 Ctrl_BaseAddress;
    u32 IsReady;
} XMatrixmult;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XMatrixmult_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XMatrixmult_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XMatrixmult_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XMatrixmult_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
#ifdef SDT
int XMatrixmult_Initialize(XMatrixmult *InstancePtr, UINTPTR BaseAddress);
XMatrixmult_Config* XMatrixmult_LookupConfig(UINTPTR BaseAddress);
#else
int XMatrixmult_Initialize(XMatrixmult *InstancePtr, u16 DeviceId);
XMatrixmult_Config* XMatrixmult_LookupConfig(u16 DeviceId);
#endif
int XMatrixmult_CfgInitialize(XMatrixmult *InstancePtr, XMatrixmult_Config *ConfigPtr);
#else
int XMatrixmult_Initialize(XMatrixmult *InstancePtr, const char* InstanceName);
int XMatrixmult_Release(XMatrixmult *InstancePtr);
#endif

void XMatrixmult_Start(XMatrixmult *InstancePtr);
u32 XMatrixmult_IsDone(XMatrixmult *InstancePtr);
u32 XMatrixmult_IsIdle(XMatrixmult *InstancePtr);
u32 XMatrixmult_IsReady(XMatrixmult *InstancePtr);
void XMatrixmult_EnableAutoRestart(XMatrixmult *InstancePtr);
void XMatrixmult_DisableAutoRestart(XMatrixmult *InstancePtr);

void XMatrixmult_Set_matrix_in_1(XMatrixmult *InstancePtr, u64 Data);
u64 XMatrixmult_Get_matrix_in_1(XMatrixmult *InstancePtr);
void XMatrixmult_Set_matrix_in_2(XMatrixmult *InstancePtr, u64 Data);
u64 XMatrixmult_Get_matrix_in_2(XMatrixmult *InstancePtr);
void XMatrixmult_Set_size(XMatrixmult *InstancePtr, u32 Data);
u32 XMatrixmult_Get_size(XMatrixmult *InstancePtr);
void XMatrixmult_Set_matrix_out(XMatrixmult *InstancePtr, u64 Data);
u64 XMatrixmult_Get_matrix_out(XMatrixmult *InstancePtr);

void XMatrixmult_InterruptGlobalEnable(XMatrixmult *InstancePtr);
void XMatrixmult_InterruptGlobalDisable(XMatrixmult *InstancePtr);
void XMatrixmult_InterruptEnable(XMatrixmult *InstancePtr, u32 Mask);
void XMatrixmult_InterruptDisable(XMatrixmult *InstancePtr, u32 Mask);
void XMatrixmult_InterruptClear(XMatrixmult *InstancePtr, u32 Mask);
u32 XMatrixmult_InterruptGetEnabled(XMatrixmult *InstancePtr);
u32 XMatrixmult_InterruptGetStatus(XMatrixmult *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
