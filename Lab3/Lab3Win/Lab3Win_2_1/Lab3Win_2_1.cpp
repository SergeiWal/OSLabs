#include <iostream>
#include <Windows.h>

int main()
{
    DWORD pid = GetCurrentProcessId();
    for (int i = 0;i < 50;i++) {
        Sleep(1000);
        std::cout << "WSA3Win_2_1: " << pid << std::endl;
    }
}
