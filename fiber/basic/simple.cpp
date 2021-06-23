// https://docs.microsoft.com/zh-tw/windows/win32/procthread/using-fibers

#include <windows.h>
#include <stdio.h>


LPVOID g_lpFiber[3];

VOID __stdcall func1(LPVOID lpParameter)
{
    LPVOID lpCurrentFiber = GetCurrentFiber();
    if (lpCurrentFiber != g_lpFiber[1]) {
        puts("It's imposible, just demos how GetCurrentFiber works");
        exit(-1);
    }

    char *msg = (char *)lpParameter;
    puts(msg);
    SwitchToFiber(g_lpFiber[2]);
    puts("fiber1 back again!");
    SwitchToFiber(g_lpFiber[0]);
}

VOID __stdcall func2(LPVOID lpParameter)
{
    char *msg = (char *)lpParameter;
    puts(msg);
    SwitchToFiber(g_lpFiber[1]);
}

int __cdecl main(int argc, TCHAR* argv[])
{
    char msg0[] = "Not used";
    char msg1[] = "I'm fiber1, call fiber2";
    char msg2[] = "I'm fiber2, call fiber1";

    g_lpFiber[0] = ConvertThreadToFiber(msg0);
    g_lpFiber[1] = CreateFiber(0, func1, msg1);
    g_lpFiber[2] = CreateFiber(0, func2, msg2);
    if (!g_lpFiber[0] || !g_lpFiber[1] || !g_lpFiber[2])
    {
        printf("CreateFiber error (%d)\n", GetLastError());
        return -1;
    }

    puts("call fiber1");
    SwitchToFiber(g_lpFiber[1]);
    puts("back to main\n");


    DeleteFiber(g_lpFiber[1]);
    DeleteFiber(g_lpFiber[2]);

    return 0;
}