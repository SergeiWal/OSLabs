#include <iostream>
#include <Windows.h>

int main()
{
    DWORD pid = GetCurrentProcessId();
    for (int i = 0;i < 1000;++i) {
        std::cout << "pid: " << pid << std::endl;
        Sleep(1000);
    }
}

