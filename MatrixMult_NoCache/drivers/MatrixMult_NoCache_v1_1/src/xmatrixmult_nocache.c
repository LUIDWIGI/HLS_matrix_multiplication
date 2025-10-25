// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
// Tool Version Limit: 2025.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xmatrixmult_nocache.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XMatrixmult_nocache_CfgInitialize(XMatrixmult_nocache *InstancePtr, XMatrixmult_nocache_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Ctrl_BaseAddress = ConfigPtr->Ctrl_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XMatrixmult_nocache_Start(XMatrixmult_nocache *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmult_nocache_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_AP_CTRL) & 0x80;
    XMatrixmult_nocache_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XMatrixmult_nocache_IsDone(XMatrixmult_nocache *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmult_nocache_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XMatrixmult_nocache_IsIdle(XMatrixmult_nocache *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmult_nocache_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XMatrixmult_nocache_IsReady(XMatrixmult_nocache *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmult_nocache_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XMatrixmult_nocache_EnableAutoRestart(XMatrixmult_nocache *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmult_nocache_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_AP_CTRL, 0x80);
}

void XMatrixmult_nocache_DisableAutoRestart(XMatrixmult_nocache *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmult_nocache_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_AP_CTRL, 0);
}

void XMatrixmult_nocache_Set_matrix_in_1(XMatrixmult_nocache *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmult_nocache_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_MATRIX_IN_1_DATA, (u32)(Data));
    XMatrixmult_nocache_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_MATRIX_IN_1_DATA + 4, (u32)(Data >> 32));
}

u64 XMatrixmult_nocache_Get_matrix_in_1(XMatrixmult_nocache *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmult_nocache_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_MATRIX_IN_1_DATA);
    Data += (u64)XMatrixmult_nocache_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_MATRIX_IN_1_DATA + 4) << 32;
    return Data;
}

void XMatrixmult_nocache_Set_matrix_in_2(XMatrixmult_nocache *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmult_nocache_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_MATRIX_IN_2_DATA, (u32)(Data));
    XMatrixmult_nocache_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_MATRIX_IN_2_DATA + 4, (u32)(Data >> 32));
}

u64 XMatrixmult_nocache_Get_matrix_in_2(XMatrixmult_nocache *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmult_nocache_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_MATRIX_IN_2_DATA);
    Data += (u64)XMatrixmult_nocache_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_MATRIX_IN_2_DATA + 4) << 32;
    return Data;
}

void XMatrixmult_nocache_Set_size(XMatrixmult_nocache *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmult_nocache_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_SIZE_DATA, Data);
}

u32 XMatrixmult_nocache_Get_size(XMatrixmult_nocache *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmult_nocache_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_SIZE_DATA);
    return Data;
}

void XMatrixmult_nocache_Set_matrix_out(XMatrixmult_nocache *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmult_nocache_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_MATRIX_OUT_DATA, (u32)(Data));
    XMatrixmult_nocache_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_MATRIX_OUT_DATA + 4, (u32)(Data >> 32));
}

u64 XMatrixmult_nocache_Get_matrix_out(XMatrixmult_nocache *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmult_nocache_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_MATRIX_OUT_DATA);
    Data += (u64)XMatrixmult_nocache_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_MATRIX_OUT_DATA + 4) << 32;
    return Data;
}

void XMatrixmult_nocache_InterruptGlobalEnable(XMatrixmult_nocache *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmult_nocache_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_GIE, 1);
}

void XMatrixmult_nocache_InterruptGlobalDisable(XMatrixmult_nocache *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmult_nocache_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_GIE, 0);
}

void XMatrixmult_nocache_InterruptEnable(XMatrixmult_nocache *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMatrixmult_nocache_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_IER);
    XMatrixmult_nocache_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_IER, Register | Mask);
}

void XMatrixmult_nocache_InterruptDisable(XMatrixmult_nocache *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMatrixmult_nocache_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_IER);
    XMatrixmult_nocache_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_IER, Register & (~Mask));
}

void XMatrixmult_nocache_InterruptClear(XMatrixmult_nocache *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmult_nocache_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_ISR, Mask);
}

u32 XMatrixmult_nocache_InterruptGetEnabled(XMatrixmult_nocache *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMatrixmult_nocache_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_IER);
}

u32 XMatrixmult_nocache_InterruptGetStatus(XMatrixmult_nocache *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMatrixmult_nocache_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_NOCACHE_CTRL_ADDR_ISR);
}

