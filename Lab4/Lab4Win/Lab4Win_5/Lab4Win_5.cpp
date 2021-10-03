#include <iostream>
#include <Windows.h>

static DWORD pid;

DWORD WINAPI T1_05()
{
	DWORD tid = GetCurrentThreadId();
	for (int i = 0;i < 50;++i) {
		std::cout << std::endl << "-----T1----" << std::endl;
		std::cout << "t1 pid: " << pid << std::endl;
		std::cout << "t1 tid: " << tid << std::endl << std::endl;
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI T2_05()
{
	DWORD tid = GetCurrentThreadId();
	for (int i = 0;i < 125;++i) {
		std::cout << std::endl << "-----T2----" << std::endl;
		std::cout << "t2 pid: " << pid << std::endl;
		std::cout << "t2 tid: " << tid << std::endl << std::endl;
		Sleep(1000);
	}
	return 0;
}

int main()
{
	pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	DWORD Thread1 = NULL;
	DWORD Thread2 = NULL;

	HANDLE handleT1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)T1_05, NULL, 0, &Thread1);
	HANDLE handleT2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)T2_05, NULL, 0, &Thread2);

	for (int i = 0;i < 100;++i) {

		if (i==40) {
			CloseHandle(handleT2);
		}

		std::cout << "Parent thread -------" << std::endl;
		std::cout << "parent pid: " << pid << std::endl;
		std::cout << "parent tid: " << tid << std::endl;
		std::cout << "child tid T1: " << Thread1 << std::endl;
		std::cout << "child tid T2: " << Thread2 << std::endl;
		Sleep(1000);
	}

	WaitForSingleObject(handleT1, INFINITE);
	CloseHandle(handleT1);

	return 0;
}