#pragma warning( disable : 4996 )

#include <windows.h>
#include <stdio.h>
#include "resource.h"

int main()
{
    HGLOBAL hResLoad;
    HMODULE hExe;
    HRSRC hRes;
    HANDLE hUpdateRes;
    LPVOID lpResLock; 


    hRes = FindResource(NULL, MAKEINTRESOURCE(IDR_MYTYPE1), L"MYTYPE");
    if (hRes == NULL)
    {
        printf("FindResource failed.\n");
        return 0;
    }

    hResLoad = LoadResource(NULL, hRes);
    if (hResLoad == NULL)
    {
        printf("LoadResource failed.\n");
        return 0;
    }

    lpResLock = LockResource(hResLoad);
    if (lpResLock == NULL)
    {
        printf("LockResource failed\n");
        return 0;
    }

    int sz = SizeofResource(NULL, hRes);
    wprintf(L"%s\n", (wchar_t*)lpResLock);
}