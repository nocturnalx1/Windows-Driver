#include "pch.h"
#include <stdio.h>
#include <tchar.h> 
#include <windows.h>
#include <winioctl.h>

// 定义跟一个约定的控制码0x800
#define IOCTL_KILL CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)

// 主函数
int _tmain(int argc, _TCHAR* argv[])
{
	// 打开符号（设备句柄）
	HANDLE hDevice = CreateFile(L"\\\\.\\MTKill", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		printf("Failed To Obtain Device Handle!");
		return -1;
	}

	DWORD len = 0;
	UCHAR buffer[20];
	memset(buffer, 0x00, 20);

	long pid = 0;

	// 接收用户输入的pid
	printf("Please Enter the Process ID : ");
	scanf_s("%d", &pid);

	// 发送pid给驱动
	BOOL status = DeviceIoControl(hDevice, IOCTL_KILL, &pid, 4, buffer, 20, &len, NULL);

	return 0;
}