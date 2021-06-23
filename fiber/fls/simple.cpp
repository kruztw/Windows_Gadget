// FLS : Fiber Local Storage

#include <windows.h>
#include <stdio.h>

DWORD g_dwSlot = 0;
char msg[] = "hello";

// trigger point: FlsFree, DeleteFiber, FlsAlloc �b���� fiber �I�s, �N�k���� fiber ��
void callback(PVOID args)
{
    printf("%s\n", (char*)FlsGetValue(g_dwSlot)); // �I�s callback ��, value �|�Q�M��
}

int main()
{
    g_dwSlot = FlsAlloc(callback);
    FlsSetValue(g_dwSlot, msg);
    printf("%s\n", (char*)FlsGetValue(g_dwSlot));
    FlsFree(g_dwSlot);
}
