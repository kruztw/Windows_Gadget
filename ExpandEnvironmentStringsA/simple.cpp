#include <windows.h>
#include <stdio.h>

int main()
{
	char result[0x100] = {};
	ExpandEnvironmentStringsA("%ALLUSERSPROFILE%", result, sizeof(result));
	printf("%s\n", result);
}