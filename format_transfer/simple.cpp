#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>


int main()
{
    LPCTSTR format_LPCTSTR = L"LPCTSTR";
    TCHAR format_tchar[10];
    LPCWSTR format_LPCWSTR = L"LPCWSTR";
    wchar_t format_wchart[10] = L"wchart";
    LPVOID format_LPVOID = format_wchart;

    // LPCWSTR -> LPWSTR
    LPWSTR  format_LPWSTR = const_cast<LPWSTR>(format_LPCWSTR);

    // LPCTSTR -> tchar
    StringCchCopy(format_tchar, 10, format_LPCTSTR);

    _tprintf(TEXT("print tchar: %s\n"), format_tchar);
    wprintf(L"print LPVOID: %s\n", (wchar_t*)format_LPVOID);
}

