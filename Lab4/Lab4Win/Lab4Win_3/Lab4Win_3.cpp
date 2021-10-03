#include <iostream>
#include <Windows.h>

static DWORD pid;

DWORD WINAPI T1_03()
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

DWORD WINAPI T2_03()
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

	HANDLE handleT1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)T1_03, NULL, 0, &Thread1);
	HANDLE handleT2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)T2_03, NULL, 0, &Thread2);

	for (int i = 0;i < 100;++i) {

		if (i==20) {
			SuspendThread(handleT1);
			std::cout << "Thread 1 is suspended" << std::endl;
		}
		if (i == 60) {
			ResumeThread(handleT1);
			std::cout << "Thread 1 is resume" << std::endl;
		}
		if (i == 40) {
			SuspendThread(handleT2);
			std::cout << "Thread 2 is suspended" << std::endl;
		}

		std::cout << "Parent thread -------" << std::endl;
		std::cout << "parent pid: " << pid << std::endl;
		std::cout << "parent tid: " << tid << std::endl;
		std::cout << "child tid T1: " << Thread1 << std::endl;
		std::cout << "child tid T2: " << Thread2 << std::endl;
		Sleep(1000);
	}
	ResumeThread(handleT2);
	std::cout << "Thread 2 is resume" << std::endl;

	WaitForSingleObject(handleT1, INFINITE);
	CloseHandle(handleT1);

	WaitForSingleObject(handleT2, INFINITE);
	CloseHandle(handleT2);

	return 0;
}