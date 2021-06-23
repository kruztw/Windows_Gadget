#include <windows.h>
#include <stdio.h>
#include <winbase.h>

int main()
{
	char result[0x100] = {};
	// xxx.ini ¦ì¸m:  HKEY_LOCAL_MACHINE\Software\Microsoft\Windows NT\CurrentVersion\IniFileMapping 
	GetProfileStringA(NULL, NULL, "not found", result, sizeof(result));
	for (int i = 0; i < 0x100; i++) {
		if (result[i])
			printf("%c", result[i]);
		else
			printf("\n");
	}

	GetProfileStringA("Windows", "Spooler", "not found", result, sizeof(result));
	printf("result: %s\n", result);
}