// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
// Tool Version Limit: 2025.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XMATRIXMULT_NOCACHE_H
#define XMATRIXMULT_NOCACHE_H

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
#include "xmatrixmult_nocache_hw.h"

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
} XMatrixmult_nocache_Config;
#endif

typedef struct {
    u64 Ctrl_BaseAddress;
    u32 IsReady;
} XMatrixmult_nocache;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XMatrixmult_nocache_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XMatrixmult_nocache_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XMatrixmult_nocache_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XMatrixmult_nocache_ReadReg(BaseAddress, RegOffset) \
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
int XMatrixmult_nocache_Initialize(XMatrixmult_nocache *InstancePtr, UINTPTR BaseAddress);
XMatrixmult_nocache_Config* XMatrixmult_nocache_LookupConfig(UINTPTR BaseAddress);
#else
int XMatrixmult_nocache_Initialize(XMatrixmult_nocache *InstancePtr, u16 DeviceId);
XMatrixmult_nocache_Config* XMatrixmult_nocache_LookupConfig(u16 DeviceId);
#endif
int XMatrixmult_nocache_CfgInitialize(XMatrixmult_nocache *InstancePtr, XMatrixmult_nocache_Config *ConfigPtr);
#else
int XMatrixmult_nocache_Initialize(XMatrixmult_nocache *InstancePtr, const char* InstanceName);
int XMatrixmult_nocache_Release(XMatrixmult_nocache *InstancePtr);
#endif

void XMatrixmult_nocache_Start(XMatrixmult_nocache *InstancePtr);
u32 XMatrixmult_nocache_IsDone(XMatrixmult_nocache *InstancePtr);
u32 XMatrixmult_nocache_IsIdle(XMatrixmult_nocache *InstancePtr);
u32 XMatrixmult_nocache_IsReady(XMatrixmult_nocache *InstancePtr);
void XMatrixmult_nocache_EnableAutoRestart(XMatrixmult_nocache *InstancePtr);
void XMatrixmult_nocache_DisableAutoRestart(XMatrixmult_nocache *InstancePtr);

void XMatrixmult_nocache_Set_matrix_in_1(XMatrixmult_nocache *InstancePtr, u64 Data);
u64 XMatrixmult_nocache_Get_matrix_in_1(XMatrixmult_nocache *InstancePtr);
void XMatrixmult_nocache_Set_matrix_in_2(XMatrixmult_nocache *InstancePtr, u64 Data);
u64 XMatrixmult_nocache_Get_matrix_in_2(XMatrixmult_nocache *InstancePtr);
void XMatrixmult_nocache_Set_size(XMatrixmult_nocache *InstancePtr, u32 Data);
u32 XMatrixmult_nocache_Get_size(XMatrixmult_nocache *InstancePtr);
void XMatrixmult_nocache_Set_matrix_out(XMatrixmult_nocache *InstancePtr, u64 Data);
u64 XMatrixmult_nocache_Get_matrix_out(XMatrixmult_nocache *InstancePtr);

void XMatrixmult_nocache_InterruptGlobalEnable(XMatrixmult_nocache *InstancePtr);
void XMatrixmult_nocache_InterruptGlobalDisable(XMatrixmult_nocache *InstancePtr);
void XMatrixmult_nocache_InterruptEnable(XMatrixmult_nocache *InstancePtr, u32 Mask);
void XMatrixmult_nocache_InterruptDisable(XMatrixmult_nocache *InstancePtr, u32 Mask);
void XMatrixmult_nocache_InterruptClear(XMatrixmult_nocache *InstancePtr, u32 Mask);
u32 XMatrixmult_nocache_InterruptGetEnabled(XMatrixmult_nocache *InstancePtr);
u32 XMatrixmult_nocache_InterruptGetStatus(XMatrixmult_nocache *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
