#include <iostream>
#include <Windows.h>

int main()
{
	LPCWSTR Lab3Win_2_1_path = L"E:\\GIT\\OSLabs\\Lab3\\Lab3Win\\Debug\\Lab3Win_2_1.exe";
	LPCWSTR Lab3Win_2_2_path = L"E:\\GIT\\OSLabs\\Lab3\\Lab3Win\\Debug\\Lab3Win_2_2.exe";
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInfo;
	ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
	startupInfo.cb = sizeof(STARTUPINFO);

	if (CreateProcess(Lab3Win_2_1_path, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInfo))
	{
		std::cout << "-- Process Lab3Win_2_1 is created\n";
	}
	else
	{
		std::cout << "-- Process Lab3Win_2_1 is not created\n";
	}

	if (CreateProcess(Lab3Win_2_2_path, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInfo))
	{
		std::cout << "-- Process Lab3Win_2_2 is created\n";
	}
	else
	{
		std::cout << "-- Process Lab3Win_2_2 is not created\n";
	}


	DWORD pid = GetCurrentProcessId();
	for (int i = 0;i < 100;i++) {
		Sleep(1000);
		std::cout << "WSA3Win_2: " << pid << std::endl;
	}

	WaitForSingleObject(processInfo.hProcess, INFINITE);
	CloseHandle(processInfo.hProcess);
}