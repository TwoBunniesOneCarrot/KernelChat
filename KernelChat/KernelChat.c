#include "KernelChat.h"

VOID KernelChat_Unload(PDRIVER_OBJECT DriverObject);
NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pusRegistryPath);
BOOLEAN KernelChat_IsStringTerminated(PCHAR pString, UINT uiLength);

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pusRegistryPath)
{
	NTSTATUS NtStatus = STATUS_FAILED_DRIVER_ENTRY;
	UINT uiIndex = 0;
	PDEVICE_OBJECT pDeviceObject = NULL;
	UNICODE_STRING usDriverName, usDosDeviceName;

	pusRegistryPath = pusRegistryPath;

	DbgPrint("DriverEntry Called \r\n"); //TODO: Open debug print in the machine

	RtlInitUnicodeString(&usDriverName, L"\\Device\\KernelChat");
	RtlInitUnicodeString(&usDosDeviceName, L"\\DosDevices\\KernelChat");

	NtStatus = IoCreateDevice(pDriverObject, 0, &usDriverName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);

	if (NtStatus == STATUS_SUCCESS)
	{
		for (uiIndex = 0; uiIndex < IRP_MJ_MAXIMUM_FUNCTION; uiIndex++)		{			pDriverObject->MajorFunction[uiIndex] = KernelChat_UnSupportedFunction;		}		pDriverObject->MajorFunction[IRP_MJ_CLOSE] = KernelChat_Close;		pDriverObject->MajorFunction[IRP_MJ_CREATE] = KernelChat_Create;		pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = KernelChat_IoControl;		pDriverObject->MajorFunction[IRP_MJ_READ] = KernelChat_Read;		pDriverObject->MajorFunction[IRP_MJ_WRITE] = USE_WRITE_FUNCTION;		pDriverObject->DriverUnload = KernelChat_Unload;
		pDeviceObject->Flags |= IO_TYPE;
		pDeviceObject->Flags &= (~DO_DEVICE_INITIALIZING);
		IoCreateSymbolicLink(&usDosDeviceName, &usDriverName);
	}
	
	return NtStatus;
}

VOID KernelChat_Unload(PDRIVER_OBJECT pDriverObject)
{
	UNICODE_STRING usDosDeviceName;	DbgPrint("KernelChat_Unload Called \r\n");	RtlInitUnicodeString(&usDosDeviceName, L"\\DosDevices\\KernelChat");	IoDeleteSymbolicLink(&usDosDeviceName);	IoDeleteDevice(pDriverObject->DeviceObject);}


NTSTATUS KernelChat_Create(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_SUCCESS;	UNREFERENCED_PARAMETER(Irp);	UNREFERENCED_PARAMETER(DeviceObject);	DbgPrint("KernelChat_Create Called \r\n");	return NtStatus;}

NTSTATUS KernelChat_Close(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_SUCCESS;	UNREFERENCED_PARAMETER(Irp);	UNREFERENCED_PARAMETER(DeviceObject);	DbgPrint("KernelChat_Close Called \r\n");	return NtStatus;}

NTSTATUS KernelChat_IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_SUCCESS;	UNREFERENCED_PARAMETER(Irp);	UNREFERENCED_PARAMETER(DeviceObject);	DbgPrint("KernelChat_IoControl Called \r\n");	return NtStatus;
}

NTSTATUS KernelChat_Read(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_SUCCESS;	UNREFERENCED_PARAMETER(Irp);	UNREFERENCED_PARAMETER(DeviceObject);	DbgPrint("KernelChat_Read Called \r\n");	return NtStatus;
}

NTSTATUS KernelChat_WriteBufferedIO(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_SUCCESS;	PIO_STACK_LOCATION pIoStackIrp = NULL;	PCHAR pWriteDataBuffer;	DbgPrint("KernelChat_WriteBufferedIO Called \r\n");	pIoStackIrp = IoGetCurrentIrpStackLocation(Irp);	if (pIoStackIrp)	{		pWriteDataBuffer = (PCHAR)Irp->AssociatedIrp.SystemBuffer;		if (pWriteDataBuffer)		{			if (KernelChat_IsStringTerminated(pWriteDataBuffer, pIoStackIrp->Parameters.Write.Length))			{				DbgPrint(pWriteDataBuffer);			}		}	}	return NtStatus;}

NTSTATUS KernelChat_WriteDirectIO(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_SUCCESS;	PIO_STACK_LOCATION pIoStackIrp = NULL;	PCHAR pWriteDataBuffer;	DbgPrint("KernelChat_WriteDirectIO Called \r\n");	pIoStackIrp = IoGetCurrentIrpStackLocation(Irp);	if (pIoStackIrp)	{		pWriteDataBuffer = MmGetSystemAddressForMdlSafe(Irp->MdlAddress, NormalPagePriority);		if (pWriteDataBuffer)		{			if (KernelChat_IsStringTerminated(pWriteDataBuffer, pIoStackIrp->Parameters.Write.Length))			{				DbgPrint(pWriteDataBuffer);			}		}	}	return NtStatus;}

NTSTATUS KernelChat_WriteNeither(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_SUCCESS;	PIO_STACK_LOCATION pIoStackIrp = NULL;	PCHAR pWriteDataBuffer;	DbgPrint("KernelChat_WriteNeither Called \r\n");	pIoStackIrp = IoGetCurrentIrpStackLocation(Irp);	if (pIoStackIrp)	{		__try {			ProbeForRead(Irp->UserBuffer, pIoStackIrp->Parameters.Write.Length, TYPE_ALIGNMENT(char));			pWriteDataBuffer = Irp->UserBuffer;			if (pWriteDataBuffer)			{				if (KernelChat_IsStringTerminated(pWriteDataBuffer, pIoStackIrp->Parameters.Write.Length))				{					DbgPrint(pWriteDataBuffer);				}			}		}		__except (EXCEPTION_EXECUTE_HANDLER) {			NtStatus = GetExceptionCode();		}	}	return NtStatus;}

NTSTATUS KernelChat_UnSupportedFunction(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_NOT_SUPPORTED;	UNREFERENCED_PARAMETER(Irp);	UNREFERENCED_PARAMETER(DeviceObject);	DbgPrint("KernelChat_UnSupportedFunction Called \r\n");	return NtStatus;}

BOOLEAN KernelChat_IsStringTerminated(PCHAR pString, UINT uiLength){	BOOLEAN bStringIsTerminated = FALSE;	UINT uiIndex = 0;	while (uiIndex < uiLength && bStringIsTerminated == FALSE)	{		if (pString[uiIndex] == '\0')		{			bStringIsTerminated = TRUE;		}		else		{			uiIndex++;		}	}	return bStringIsTerminated;}