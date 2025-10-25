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
#include "xmatrixmult_nocache.h"

extern XMatrixmult_nocache_Config XMatrixmult_nocache_ConfigTable[];

#ifdef SDT
XMatrixmult_nocache_Config *XMatrixmult_nocache_LookupConfig(UINTPTR BaseAddress) {
	XMatrixmult_nocache_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XMatrixmult_nocache_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XMatrixmult_nocache_ConfigTable[Index].Ctrl_BaseAddress == BaseAddress) {
			ConfigPtr = &XMatrixmult_nocache_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XMatrixmult_nocache_Initialize(XMatrixmult_nocache *InstancePtr, UINTPTR BaseAddress) {
	XMatrixmult_nocache_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XMatrixmult_nocache_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XMatrixmult_nocache_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XMatrixmult_nocache_Config *XMatrixmult_nocache_LookupConfig(u16 DeviceId) {
	XMatrixmult_nocache_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XMATRIXMULT_NOCACHE_NUM_INSTANCES; Index++) {
		if (XMatrixmult_nocache_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XMatrixmult_nocache_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XMatrixmult_nocache_Initialize(XMatrixmult_nocache *InstancePtr, u16 DeviceId) {
	XMatrixmult_nocache_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XMatrixmult_nocache_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XMatrixmult_nocache_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

