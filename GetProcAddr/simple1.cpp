#include <stdio.h>
#include <Windows.h>

typedef int(_stdcall* msgboxFunc)(HWND, LPCSTR, LPCSTR, UINT);

int main()
{
	msgboxFunc msgbox = NULL;
	HMODULE hModule = LoadLibraryA("user32.dll");
	msgbox = (msgboxFunc)(GetProcAddress(hModule, "MessageBoxA"));
	(*msgbox)(NULL, "title", "content", MB_OK);
	FreeLibrary(hModule);
}