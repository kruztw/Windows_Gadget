#include <stdio.h>
#include <Windows.h>

typedef int(_stdcall* msgboxFunc)(HWND, LPCSTR, LPCSTR, UINT);

int main()
{
	msgboxFunc msgbox = NULL;
	HMODULE hModule = LoadLibraryA("user32.dll");
	msgbox = (msgboxFunc)(GetProcAddress(hModule, (PCSTR)0x864)); // C:\Windows\SysWow64\user32.dll (32bits)  0x864 -> MessageBoxA's ordinal
	(*msgbox)(NULL, "content", "title", MB_OK);
	FreeLibrary(hModule);
}