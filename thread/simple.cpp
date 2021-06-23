// windows-threads.cpp
#include <windows.h>
#include <stdio.h>

DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
    char* msg = (char*)lpParam;
    printf(msg);
    return 0;
}

int main()
{
    char msg[] = "hello world";
    // Create the thread to begin execution on its own.
    DWORD dwThreadId;
    HANDLE hThread = CreateThread(
        NULL,                   // default security attributes
        0,                      // use default stack size  
        MyThreadFunction,       // thread function name
        msg,                  // argument to thread function 
        0,                      // use default creation flags 
        &dwThreadId);           // returns the thread identifier 

    if (hThread == NULL)
    {
        ExitProcess(3);
    }

    // Wait for the thread to finish.
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    return 0;
}

