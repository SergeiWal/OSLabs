#include <iostream>
#include <Windows.h>

using namespace std;

void printProcessPrty(HANDLE h) {
    DWORD prty = GetPriorityClass(h);
    std::cout << "Current PID: " << GetCurrentProcessId() << std::endl;
    switch (prty)
    {
    case IDLE_PRIORITY_CLASS: std::cout << " ----+ priority = IDLE_PRIORITY_CLASS \n"; break;
    case BELOW_NORMAL_PRIORITY_CLASS: std::cout << " ----+ priority = BELOW_NORMAL_PRIORITY_CLASS \n"; break;
    case NORMAL_PRIORITY_CLASS: std::cout << " ----+ priority = NORMAL_PRIORITY_CLASS \n"; break;
    case ABOVE_NORMAL_PRIORITY_CLASS: std::cout << " ----+ priority = ABOVE_NORMAL_PRIORITY_CLASS \n"; break;
    case HIGH_PRIORITY_CLASS: std::cout << " ----+ priority = HIGH_PRIORITY_CLASS \n"; break;
    case REALTIME_PRIORITY_CLASS: std::cout << " ----+ priority = REALTIME_PRIORITY_CLASS \n"; break;
    default: std::cout << " ----+ priority = ? \n"; break;
    }
}

void printThreadPrty(HANDLE h) {
    DWORD prty = GetThreadPriority(h);
    DWORD ccpu = SetThreadIdealProcessor(h, MAXIMUM_PROCESSORS);
    std::cout << "Thread priority: " << prty << std::endl;
    std::cout << "Current Thread Id: " << GetCurrentThreadId() << std::endl;
    std::cout << "Processor: " << ccpu << std::endl;
    switch (prty)
    {
    case THREAD_PRIORITY_LOWEST: std::cout << " ----+ priority = THREAD_PRIORITY_LOWEST \n"; break;
    case THREAD_PRIORITY_BELOW_NORMAL: std::cout << " ----+ priority = THREAD_PRIORITY_BELOW_NORMAL \n"; break;
    case THREAD_PRIORITY_NORMAL: std::cout << " ----+ priority = THREAD_PRIORITY_NORMAL \n"; break;
    case THREAD_PRIORITY_ABOVE_NORMAL: std::cout << " ----+ priority = THREAD_PRIORITY_ABOVE_NORMAL \n"; break;
    case THREAD_PRIORITY_HIGHEST: std::cout << " ----+ priority = THREAD_PRIORITY_HIGHEST \n"; break;
    case THREAD_PRIORITY_IDLE: std::cout << " ----+ priority = THREAD_PRIORITY_IDLE \n"; break;
    case THREAD_PRIORITY_TIME_CRITICAL: std::cout << " ----+ priority = THREAD_PRIORITY_TIME_CRITICAL \n"; break;
    default: std::cout << " ----+ priority = ? \n"; break;
    }
}

void printCycle( HANDLE hp, HANDLE ht)
{
    for (unsigned long long i = 0; i < 1000000; i++)
    {
        if (i % 1000 == 0) {
            std::cout << i << std::endl;
            printProcessPrty(hp);
            printThreadPrty(ht);
            Sleep(200);
        }
    }
    return;
}

int main()
{
    HANDLE hp = GetCurrentProcess();
    HANDLE ht = GetCurrentThread();

    try {
        printCycle(hp, ht);
    }
    catch (char* msg) {
        std::cout << "Error: " << msg << std::endl;
    }

    system("pause");
  
}