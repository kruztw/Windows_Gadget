// FLS : Fiber Local Storage

#include <windows.h>
#include <stdio.h>

DWORD g_dwSlot = 0;
char msg[] = "hello";

// trigger point: FlsFree, DeleteFiber, FlsAlloc 在哪個 fiber 呼叫, 就歸哪個 fiber 管
void callback(PVOID args)
{
    printf("%s\n", (char*)FlsGetValue(g_dwSlot)); // 呼叫 callback 時, value 會被清空
}

int main()
{
    g_dwSlot = FlsAlloc(callback);
    FlsSetValue(g_dwSlot, msg);
    printf("%s\n", (char*)FlsGetValue(g_dwSlot));
    FlsFree(g_dwSlot);
}
