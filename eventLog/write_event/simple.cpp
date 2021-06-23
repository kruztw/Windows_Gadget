/*
 * 功能: 紀錄 event 到 event logger
 *
 * event logger (控制台 -> 搜尋 event, 左邊 Windows Logs -> Application (右鍵 refresh))
*/


#include <windows.h>
#include <tchar.h>

int main()
{
    LPCWSTR const_SVCNAME = L"hello world";
    LPWSTR SVCNAME = const_cast<LPWSTR>(const_SVCNAME);

    HANDLE hEventSource;
    LPCTSTR lpszStrings[2];
    TCHAR Buffer[80] = TEXT("Double click and scroll down the text area or click Details and select XML View");
    DWORD SVC_ERROR = 5408;

    hEventSource = RegisterEventSource(NULL, SVCNAME);
    if (NULL != hEventSource)
    {
        lpszStrings[0] = SVCNAME;
        lpszStrings[1] = Buffer;

        ReportEvent(
            hEventSource,        // event log handle
            EVENTLOG_ERROR_TYPE, // event type
            9588,                // event category
            SVC_ERROR,           // event identifier
            NULL,                // no security identifier
            2,                   // size of lpszStrings array
            0,                   // no binary data
            lpszStrings,         // array of strings
            NULL);               // no binary data

        DeregisterEventSource(hEventSource);
    }

    system("pause");
    return 0;
}
