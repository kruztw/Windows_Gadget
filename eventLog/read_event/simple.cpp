#include <windows.h>
#include <winbase.h>
#include <stdio.h>

int main() {

        // 名字應該可以到 event logger 看, 控制台 -> 搜尋 event
	HANDLE hEvent = OpenEventLogA(NULL, "system");
	DWORD record_num, pnBytesRead, pnMinimunNumberOfBytesNeeded, ret;
	PDWORD record = &record_num;
	char pBuffer[0x1000] = {};
	EVENTLOGRECORD* log;

	GetOldestEventLogRecord(hEvent, record);
	printf("total record: %d\n", record_num);

	log = (EVENTLOGRECORD*)pBuffer;
	ret = ReadEventLogA(hEvent, EVENTLOG_SEQUENTIAL_READ | EVENTLOG_FORWARDS_READ, 0, pBuffer, 4096, &pnBytesRead, &pnMinimunNumberOfBytesNeeded);

	printf("EventId: %d", log->EventID);

}
