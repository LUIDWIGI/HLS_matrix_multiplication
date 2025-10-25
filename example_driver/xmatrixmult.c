// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
// Tool Version Limit: 2025.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xmatrixmult.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XMatrixmult_CfgInitialize(XMatrixmult *InstancePtr, XMatrixmult_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Ctrl_BaseAddress = ConfigPtr->Ctrl_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XMatrixmult_Start(XMatrixmult *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmult_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_AP_CTRL) & 0x80;
    XMatrixmult_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XMatrixmult_IsDone(XMatrixmult *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmult_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XMatrixmult_IsIdle(XMatrixmult *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmult_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XMatrixmult_IsReady(XMatrixmult *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmult_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XMatrixmult_EnableAutoRestart(XMatrixmult *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmult_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_AP_CTRL, 0x80);
}

void XMatrixmult_DisableAutoRestart(XMatrixmult *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmult_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_AP_CTRL, 0);
}

void XMatrixmult_Set_matrix_in_1(XMatrixmult *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmult_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_MATRIX_IN_1_DATA, (u32)(Data));
    XMatrixmult_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_MATRIX_IN_1_DATA + 4, (u32)(Data >> 32));
}

u64 XMatrixmult_Get_matrix_in_1(XMatrixmult *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmult_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_MATRIX_IN_1_DATA);
    Data += (u64)XMatrixmult_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_MATRIX_IN_1_DATA + 4) << 32;
    return Data;
}

void XMatrixmult_Set_matrix_in_2(XMatrixmult *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmult_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_MATRIX_IN_2_DATA, (u32)(Data));
    XMatrixmult_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_MATRIX_IN_2_DATA + 4, (u32)(Data >> 32));
}

u64 XMatrixmult_Get_matrix_in_2(XMatrixmult *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmult_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_MATRIX_IN_2_DATA);
    Data += (u64)XMatrixmult_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_MATRIX_IN_2_DATA + 4) << 32;
    return Data;
}

void XMatrixmult_Set_size(XMatrixmult *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmult_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_SIZE_DATA, Data);
}

u32 XMatrixmult_Get_size(XMatrixmult *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmult_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_SIZE_DATA);
    return Data;
}

void XMatrixmult_Set_matrix_out(XMatrixmult *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmult_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_MATRIX_OUT_DATA, (u32)(Data));
    XMatrixmult_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_MATRIX_OUT_DATA + 4, (u32)(Data >> 32));
}

u64 XMatrixmult_Get_matrix_out(XMatrixmult *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMatrixmult_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_MATRIX_OUT_DATA);
    Data += (u64)XMatrixmult_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_MATRIX_OUT_DATA + 4) << 32;
    return Data;
}

void XMatrixmult_InterruptGlobalEnable(XMatrixmult *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmult_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_GIE, 1);
}

void XMatrixmult_InterruptGlobalDisable(XMatrixmult *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmult_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_GIE, 0);
}

void XMatrixmult_InterruptEnable(XMatrixmult *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMatrixmult_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_IER);
    XMatrixmult_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_IER, Register | Mask);
}

void XMatrixmult_InterruptDisable(XMatrixmult *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMatrixmult_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_IER);
    XMatrixmult_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_IER, Register & (~Mask));
}

void XMatrixmult_InterruptClear(XMatrixmult *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMatrixmult_WriteReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_ISR, Mask);
}

u32 XMatrixmult_InterruptGetEnabled(XMatrixmult *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMatrixmult_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_IER);
}

u32 XMatrixmult_InterruptGetStatus(XMatrixmult *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMatrixmult_ReadReg(InstancePtr->Ctrl_BaseAddress, XMATRIXMULT_CTRL_ADDR_ISR);
}

