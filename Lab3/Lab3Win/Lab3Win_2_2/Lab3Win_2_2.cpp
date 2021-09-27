#include <iostream>
#include <Windows.h>

int main()
{
    DWORD pid = GetCurrentProcessId();
    for (int i = 0;i < 125;i++) {
        Sleep(1000);
        std::cout << "WSA3Win_2_2: " << pid << std::endl;
    }
}