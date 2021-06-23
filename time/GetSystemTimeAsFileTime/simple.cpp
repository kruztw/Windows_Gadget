#include <stdio.h>
#include <Windows.h>

int main()
{
	FILETIME lpSystemTimeAsFileTime;
	GetSystemTimeAsFileTime(&lpSystemTimeAsFileTime);
	printf("cuurrent_tick: %u\n", lpSystemTimeAsFileTime.dwLowDateTime + (lpSystemTimeAsFileTime.dwHighDateTime << 32));
}
