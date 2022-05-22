/*++
	Copyright (c) DuoWoA authors. All Rights Reserved.

	SPDX-License-Identifier: BSD-3-Clause

Module Name:

	device.h

Abstract:

	This file contains the device definitions.

Environment:

	Kernel-mode Driver Framework

--*/

#pragma once

#include "spb.h"
#include "registry.h"
#include <hwnclx.h>
#include <hwn.h>
#include "..\GPLCode\da7280.h"

EXTERN_C_START

#define HAPTICS_POOL_TAG 'HnwH'

typedef struct _SURFACE_HAPTICS_CURRENT_STATE
{
	HWN_SETTINGS CurrentState;
	struct _SURFACE_HAPTICS_CURRENT_STATE* NextState;
} SURFACE_HAPTICS_CURRENT_STATE, * PSURFACE_HAPTICS_CURRENT_STATE;

//
// The device context performs the same job as
// a WDM device extension in the driver frameworks
//
typedef struct _DEVICE_CONTEXT
{
	//
	// Device handle
	//
	WDFDEVICE Device;

	//
	// Interrupt servicing
	//
	WDFINTERRUPT InterruptObject;

	//
	// Spb (I2C) related members used for the lifetime of the device
	//
	SPB_CONTEXT I2CContext;

	//
	// Driver configuration
	//
	SURFACE_HAPTICS_CONFIG Config;

	//
	// Controller configuration
	//
	DA7280_CONFIGURATION Haptics;

	//
	// Number of vibration motors
	//
	USHORT NumberOfHapticsDevices;

	PSURFACE_HAPTICS_CURRENT_STATE CurrentStates;
	HWN_STATE PreviousState;
} DEVICE_CONTEXT, * PDEVICE_CONTEXT;

//
// This macro will generate an inline function called DeviceGetContext
// which will be used to get a pointer to the device context memory
// in a type safe manner.
//
WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DEVICE_CONTEXT, DeviceGetContext)

//
// Function to initialize the device and its callbacks
//
NTSTATUS
SurfaceHapticsCreateDevice(
	_Inout_ WDFDRIVER Driver,
	_Inout_ PWDFDEVICE_INIT DeviceInit
);

EXTERN_C_END
