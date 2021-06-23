#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

typedef int (*fptr)(void);

int main()
{
    fptr say_hi = NULL;
    HINSTANCE dllHandle = LoadLibrary(_T("Dll.dll"));
    say_hi = (fptr)GetProcAddress(dllHandle, "say_hi");
    (*say_hi)();
    FreeLibrary(dllHandle);
}
