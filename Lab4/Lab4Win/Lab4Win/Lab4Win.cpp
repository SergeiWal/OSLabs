// Lab4Win.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>

int main()
{
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	for (int i = 0;i < 100000;++i) {
		std::cout << "pid: " << pid << std::endl;
		std::cout << "tid: " << tid << std::endl << std::endl;
		Sleep(1000);
	}
}


