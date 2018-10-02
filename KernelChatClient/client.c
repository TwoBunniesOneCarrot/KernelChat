#include <windows.h>

#define BUFFERSIZE 5

int _cdecl main(int argc, char* argv[])
{
	HANDLE hFile;
	DWORD dwReturn;
	DWORD byteReading;
	TCHAR ptcBuffer[BUFFERSIZE];
	char cpReadBuffer[BUFFERSIZE];

	printf("Initialized variables \r\n");
	
	printf("Trying to create handle for \\\\.\\KernelChat");
	hFile = CreateFile("\\\\.\\KernelChat", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	printf("Created file handle");

	if (hFile)
	{
		printf("Writing value %s to \\\\.\\KernelChat", "ThisIsATest-123456");
		WriteFile(hFile, "ThisIsATest-123456", sizeof("ThisIsATest-123456"), &dwReturn, NULL);
		CloseHandle(hFile);
	}

	hFile = CreateFile("\\\\.\\KernelChat", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

	if (hFile)
	{
		printf("Trying to create handle for \\\\.\\KernelChat");
	
		if (TRUE == ReadFile(hFile, cpReadBuffer, byteReading, &byteReading, NULL))
		{
			printf("Created file handle \r\n");
			mbstowcs(ptcBuffer, cpReadBuffer, BUFFERSIZE);
			printf("%s", ptcBuffer);
		}
		CloseHandle(hFile);
	}

	return 0;
}