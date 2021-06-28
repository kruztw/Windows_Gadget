#include <windows.h>
#include <stdio.h>

DWORD WINAPI ThreadProc1(LPVOID lpParam);
DWORD WINAPI ThreadProc2(LPVOID lpParam);
HANDLE hEvent = NULL;
HANDLE hThread1 = NULL;
HANDLE hThread2 = NULL;

int main()
{
    // 感覺很像 lock, 但同時 WaitForSingleObject 又會出錯 (把 Sleep 拿掉就知道), 不知道有什麼用 ??
    hEvent = CreateEvent(NULL,        
                         FALSE,       // 是否手動設定, 自動的話會在調用該信號 thread 結束時關閉信號
                         TRUE,        // 信號初始狀態 (True : 有信號)
                         L"Globalfuckyou"); // 名字, prefix 可以用 Global 或 Local 設定變數範圍

    hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc1, NULL, 0, NULL);
    Sleep(200);
    hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc2, NULL, 0, NULL);
    Sleep(200);
    if (NULL == hThread1)
    {
        printf("create thread fail!");
    }

    return 0;
}

DWORD WINAPI ThreadProc1(LPVOID lpParam)
{
    printf("in thread1@!\n");
    DWORD dReturn = WaitForSingleObject(hEvent, INFINITE); // 有信號才能通過
    if (WAIT_OBJECT_0 == dReturn)
    {
        printf(" thread1 signaled ! \n");
    }
    
    printf("in thread1 --signal\n");
    SetEvent(hEvent);                                      // 設定成有信號
    return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParam)
{
    printf("in thread2@!\n");
    DWORD dReturn = WaitForSingleObject(hEvent, INFINITE);
    if (WAIT_OBJECT_0 == dReturn)
    {
        printf(" thread2 signaled ! \n");
    }
    printf("in thread2 --signal\n");

    return 0;
}