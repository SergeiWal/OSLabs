#include <iostream>
#include <Windows.h>

static DWORD pid;

DWORD WINAPI T1_04()
{
	DWORD tid = GetCurrentThreadId();
	for (int i = 0;i < 50;++i) {
		if (i == 25) {
			std::cout << "Thread 1 has gone to bed ..." << std::endl;
			Sleep(10000);
		}
		std::cout << std::endl << "-----T1----" << std::endl;
		std::cout << "t1 pid: " << pid << std::endl;
		std::cout << "t1 tid: " << tid << std::endl << std::endl;
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI T2_04()
{
	DWORD tid = GetCurrentThreadId();
	for (int i = 0;i < 125;++i) {
		if (i == 80) {
			std::cout << "Thread 2 has gone to bed ..." << std::endl;
			Sleep(15000);
		}
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

	HANDLE handleT1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)T1_04, NULL, 0, &Thread1);
	HANDLE handleT2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)T2_04, NULL, 0, &Thread2);

	for (int i = 0;i < 100;++i) {
		if (i == 30) {
			std::cout << "Main thread has gone to bed ..." << std::endl;
			Sleep(10000);
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

	WaitForSingleObject(handleT2, INFINITE);
	CloseHandle(handleT2);

	return 0;
}