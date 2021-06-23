#include <stdio.h>
#include <windows.h>
#include <winreg.h>

HKEY hKEY;
long regOpenResult;
DWORD dataType;
DWORD dataSize = 255;
DWORD data;

int main()
{
	regOpenResult = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v4\\Full", 0, KEY_READ, &hKEY);
	if (regOpenResult == ERROR_SUCCESS)
	{
		if (RegQueryValueExA(hKEY, "Release", NULL, &dataType, (LPBYTE)&data, &dataSize) == ERROR_SUCCESS)
					printf("value: %d\ntype: %d\n", data, dataType); // dataType: REG_DWORD
		else
			printf("key not found");
	}
	else
	{
		printf("reg open key failed¡I");
	}

	RegCloseKey(hKEY);

}