#pragma once

#include <wdm.h>

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pusRegistryPath);

typedef unsigned int UINT;
typedef char * PCHAR;

/* #define __USE_DIRECT__ */ //TODO: what is this?
/* #define __USE_BUFFERED__ */ //TODO: what is this?

NTSTATUS KernelChat_Create(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS KernelChat_Close(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS KernelChat_IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS KernelChat_Read(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS KernelChat_WriteBufferedIO(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS KernelChat_WriteDirectIO(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS KernelChat_WriteNeither(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS KernelChat_UnSupportedFunction(PDEVICE_OBJECT DeviceObject, PIRP Irp);

#ifdef __USE_DIRECT__
#define IO_TYPE DO_DIRECT_IO
#define USE_WRITE_FUNCTION KernelChat_WriteDirectIO
#endif

#ifdef __USE_BUFFERED__
#define IO_TYPE DO_BUFFERED_IO
#define USE_WRITE_FUNCTION KernelChat_WriteBufferedIO
#endif

#ifndef IO_TYPE
#define IO_TYPE 0
#define USE_WRITE_FUNCTION KernelChat_WriteNeither
#endif
