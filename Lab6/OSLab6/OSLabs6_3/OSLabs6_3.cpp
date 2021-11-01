#include <iostream>
#include <Windows.h>

#define PG (4096)

using namespace std;


int main()
{
    int pg = 256;
    setlocale(LC_ALL, "rus");

    SYSTEM_INFO system_info;
    GetSystemInfo(&system_info);

    int* virtArray = (int*)VirtualAlloc(NULL, pg * PG, MEM_COMMIT, PAGE_READWRITE);
    for (int i = 0; i < pg * PG / 4; i++)
    {
        virtArray[i] = i;
    }

    int index = ('V' * system_info.dwPageSize + (L'A' << 4) + (L'L' << 4)) / sizeof(int);
    cout << virtArray[index] << endl;

    cout << endl;
}