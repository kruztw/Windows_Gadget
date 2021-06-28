#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int main()
{
	int				result;
	TCHAR			filename[MAX_PATH] = _T("wtf file");
	TCHAR	FileDlgTitle[] = _T("Locate IExample.dll to register it");
	TCHAR	FileDlgExt[] = _T("DLL files\000*.dll\000\000");
	OPENFILENAME	ofn;

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFilter = &FileDlgExt[0];
	ofn.lpstrFile = &filename[0];
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = &FileDlgTitle[0];
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_PATHMUSTEXIST;
	result = GetOpenFileName(&ofn);
	_tprintf(TEXT("%s"), filename);
}
