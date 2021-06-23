#include <windows.h>
#include <stdio.h>


int __cdecl main(int argc, TCHAR* argv[])
{
    HANDLE file1, file2;
    LPBYTE buff[2];
    DWORD dwBytesWritten, dwBytesRead;

    file1 = CreateFile(
        LPCWSTR(L"input_file.txt"),
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_SEQUENTIAL_SCAN,
        NULL
    );

    file2 = CreateFile(
        LPCWSTR(L"./output_file.txt"),
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_NEW,
        FILE_FLAG_SEQUENTIAL_SCAN,
        NULL
    );

    if (file1 == INVALID_HANDLE_VALUE || file2 == INVALID_HANDLE_VALUE)
    {
        printf("CreateFile2 error (%d)\n", GetLastError());
        return -1;
    }

    while (ReadFile(file1, buff, sizeof(buff), &dwBytesRead, NULL) && dwBytesRead > 0)
    {
        WriteFile(file2, buff, dwBytesRead, &dwBytesWritten, NULL);
    }

    CloseHandle(file1);
    CloseHandle(file2);
}