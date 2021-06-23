// 註: 尚未測試過

#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdio.h>


int main()
{
    LPCTSTR format_LPCTSTR = L"aaaa";
    TCHAR format_tchar[10];
    LPCWSTR format_LPCWSTR = L"llll";
    LPCWSTR format_LPCWSTR = L"aaaa";

    // LPCWSTR -> LPWSTR
    LPWSTR  format_LPWSTR  = const_cast<LPWSTR>(format_LPCWSTR);

    // LPCTSTR -> tchar
    StringCchCopy(format_tchar, 10, format_LPCTSTR);


    _tprintf(TEXT("%s aaaa"), format_tchar);


}
