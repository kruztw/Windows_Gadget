#include <windows.h>
#include <stdio.h>

int main()
{
    TCHAR path[0x100];

    GetModuleFileName(NULL, path, sizeof(path));
    printf("path = %s\n", path);

    return 0;
}