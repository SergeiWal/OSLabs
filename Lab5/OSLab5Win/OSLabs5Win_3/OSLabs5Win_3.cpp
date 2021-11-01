#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>


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

void printCycle1()
{
    HANDLE hp = GetCurrentProcess();
    HANDLE ht = GetCurrentThread();
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

void printCycle2()
{
    HANDLE hp = GetCurrentProcess();
    HANDLE ht = GetCurrentThread();
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


void SetProccesPriority(HANDLE hp, int priority)
{
    if (priority == 1)
    {
        SetPriorityClass(hp, IDLE_PRIORITY_CLASS);
    }
    if (priority == 2)
    {
        SetPriorityClass(hp, NORMAL_PRIORITY_CLASS);
    }
    if (priority == 3)
    {
        SetPriorityClass(hp, HIGH_PRIORITY_CLASS);
    }
    if (priority == 4)
    {
        SetPriorityClass(hp, REALTIME_PRIORITY_CLASS);
    }
}


void SetPriorityThread(HANDLE hp, int priority)
{
    switch (priority)
    {
    case 1: SetThreadPriority(hp, THREAD_PRIORITY_IDLE); break;
    case 2: SetThreadPriority(hp, THREAD_PRIORITY_LOWEST); break;
    case 3: SetThreadPriority(hp, THREAD_PRIORITY_BELOW_NORMAL); break;
    case 4: SetThreadPriority(hp, THREAD_PRIORITY_NORMAL); break;
    case 5: SetThreadPriority(hp, THREAD_PRIORITY_ABOVE_NORMAL); break;
    case 6: SetThreadPriority(hp, THREAD_PRIORITY_HIGHEST); break;
    case 7: SetThreadPriority(hp, THREAD_PRIORITY_TIME_CRITICAL); break;
    default:  SetThreadPriority(hp, THREAD_PRIORITY_NORMAL); break;
    }
}


int main(int argc, char* argv[])
{
    for (int i = 0; i < argc; i++)
    {
        std::cout << "arg" << i << ": " << argv[i] << "\n";
    }

    HANDLE hp = GetCurrentProcess();
    try
    {
        {
            DWORD pa = NULL, sa = NULL, icpu = -1;
            if (!GetProcessAffinityMask(hp, &pa, &sa)) throw "GetProcessAffinityMask";
            std::cout << " Process Affinity Mask: " << std::showbase << std::hex << pa << "\n";
            std::cout << " System Affinity Mask: " << std::showbase << std::hex << sa << "\n";
            std::cout << std::dec << std::noshowbase << "\n\n";

            if (argv[1] != NULL)
            {
                unsigned long long mask;
                sscanf_s(argv[1], "%d", &mask);
                if (!SetProcessAffinityMask(hp, mask)) throw "SetProcessAffinityMask";

                if (!GetProcessAffinityMask(hp, &pa, &sa)) throw "GetProcessAffinityMask";
                std::cout << " Process Affinity Mask: " << std::showbase << std::hex << pa << "\n";
                std::cout << " System Affinity Mask: " << std::showbase << std::hex << sa << "\n";
                std::cout << std::dec << std::noshowbase;


                if (argv[2] != NULL)
                {
                    int priority = 0;
                    sscanf_s(argv[2], "%d", &priority);
                    SetProccesPriority(GetCurrentProcess(), priority);

                    if (argv[3] != NULL)
                    {
                        sscanf_s(argv[3], "%d", &priority);

                        DWORD ChildId1 = NULL;
                        HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)printCycle1, NULL, CREATE_SUSPENDED, &ChildId1);
                        SetPriorityThread(hChild1, priority);
                        ResumeThread(hChild1);

                        if (argv[4] != NULL)
                        {
                            sscanf_s(argv[4], "%d", &priority);
                            DWORD ChildId2 = NULL;
                            HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)printCycle2, NULL, CREATE_SUSPENDED, &ChildId2);
                            SetPriorityThread(hChild2, priority);
                            ResumeThread(hChild2);

                        }
                    }

                }
            }

        }
    }
    catch (char* msg) { std::cout << "Error " << msg << "\n"; }


    system("pause");
}