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
		for (uiIndex = 0; uiIndex < IRP_MJ_MAXIMUM_FUNCTION; uiIndex++)
		pDeviceObject->Flags |= IO_TYPE;
		pDeviceObject->Flags &= (~DO_DEVICE_INITIALIZING);
		IoCreateSymbolicLink(&usDosDeviceName, &usDriverName);
	}
	
	return NtStatus;
}

VOID KernelChat_Unload(PDRIVER_OBJECT pDriverObject)
{
	UNICODE_STRING usDosDeviceName;


NTSTATUS KernelChat_Create(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_SUCCESS;

NTSTATUS KernelChat_Close(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_SUCCESS;

NTSTATUS KernelChat_IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_SUCCESS;
}

NTSTATUS KernelChat_Read(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_SUCCESS;
}

NTSTATUS KernelChat_WriteBufferedIO(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_SUCCESS;

NTSTATUS KernelChat_WriteDirectIO(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_SUCCESS;

NTSTATUS KernelChat_WriteNeither(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_SUCCESS;

NTSTATUS KernelChat_UnSupportedFunction(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS NtStatus = STATUS_NOT_SUPPORTED;

BOOLEAN KernelChat_IsStringTerminated(PCHAR pString, UINT uiLength)