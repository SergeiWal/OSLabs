#include <Windows.h>
#include <iostream>
#include <bitset>

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
    std::cout << "Current Thread Id: " << GetCurrentThreadId() << std::endl;
    std::cout << "Processor: " << ccpu << std::endl;
    std::cout << "Processors count: " << MAXIMUM_PROCESSORS << std::endl;
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

int main()
{
    HANDLE hp = GetCurrentProcess();
    HANDLE ht = GetCurrentThread();

    try {
        DWORD pa = NULL, sa = NULL, icpu = -1;
        if (!GetProcessAffinityMask(hp, &pa, &sa))throw "GetProcessAffinityMask";
        std::bitset<8> x(pa);
        std::cout << "Process Affinity Mask: " << std::showbase << x << "\n";
        std::bitset<8> y(sa);
        std::cout << "System Affinity Mask: " << std::showbase << y << "\n";
    }
    catch (char* msg) {
        std::cout << "Error: " << msg << std::endl;
    }
    std::cout << std::dec << std::noshowbase;
    printProcessPrty(hp);
    printThreadPrty(ht);
    std::cout << std::endl;
}

