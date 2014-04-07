#include <ntddk.h>

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath);
VOID UnloadRoutine(IN PDRIVER_OBJECT DriverObject);

#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(PAGE, UnloadRoutine)

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegisrtyPath) {
  DriverObject->DriverUnload = UnloadRoutine;
  DbgPrint("Driver says Hello!\n");
  return STATUS_SUCCESS;
}

VOID UnloadRoutine(IN PDRIVER_OBJECT DriverObject) {
  DbgPrint("Driver says Goodbye!\n");
}