// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
// Tool Version Limit: 2025.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#ifdef SDT
#include "xparameters.h"
#endif
#include "xmatrixmult.h"

extern XMatrixmult_Config XMatrixmult_ConfigTable[];

#ifdef SDT
XMatrixmult_Config *XMatrixmult_LookupConfig(UINTPTR BaseAddress) {
	XMatrixmult_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XMatrixmult_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XMatrixmult_ConfigTable[Index].Ctrl_BaseAddress == BaseAddress) {
			ConfigPtr = &XMatrixmult_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XMatrixmult_Initialize(XMatrixmult *InstancePtr, UINTPTR BaseAddress) {
	XMatrixmult_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XMatrixmult_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XMatrixmult_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XMatrixmult_Config *XMatrixmult_LookupConfig(u16 DeviceId) {
	XMatrixmult_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XMATRIXMULT_NUM_INSTANCES; Index++) {
		if (XMatrixmult_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XMatrixmult_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XMatrixmult_Initialize(XMatrixmult *InstancePtr, u16 DeviceId) {
	XMatrixmult_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XMatrixmult_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XMatrixmult_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

