// https://www.codeproject.com/Articles/13601/COM-in-plain-C   # x86 

#include <windows.h>
#include <objbase.h>
#include <stdio.h>
#include <tchar.h>
#include <initguid.h>

// {6899A2A3-405B-44d4-A415-E08CEE2A97CB}
DEFINE_GUID(CLSID_IExample, 0x6899a2a3, 0x405b, 0x44d4, 0xa4, 0x15, 0xe0, 0x8c, 0xee, 0x2a, 0x97, 0xcb);
// {74666CAC-C2B1-4fa8-A049-97F3214802F0}
DEFINE_GUID(IID_IExample, 0x74666cac, 0xc2b1, 0x4fa8, 0xa0, 0x49, 0x97, 0xf3, 0x21, 0x48, 0x2, 0xf0);

DECLARE_INTERFACE_(IExample, IUnknown)
{
	STDMETHOD(QueryInterface)		(THIS_ REFIID, void**) PURE;
	STDMETHOD_(ULONG, AddRef)		(THIS) PURE;
	STDMETHOD_(ULONG, Release)		(THIS) PURE;
	STDMETHOD(SetString)			(THIS_ char*) PURE;
	STDMETHOD(GetString)			(THIS_ char*, DWORD) PURE;
};

static const TCHAR	ObjectDescription[] = _T("IExample COM component");
static const TCHAR	ClassKeyName[] = _T("Software\\Classes");
static const TCHAR	CLSID_Str[] = _T("CLSID");
static const TCHAR	InprocServer32Name[] = _T("InprocServer32");
static const TCHAR	ThreadingModel[] = _T("ThreadingModel");
static const TCHAR	BothStr[] = _T("both");
static const TCHAR	GUID_Format[] = _T("{%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}");

static void stringFromCLSID(LPTSTR buffer, REFCLSID ri)
{
	wsprintf(buffer, &GUID_Format[0],
		((REFCLSID)ri)->Data1, ((REFCLSID)ri)->Data2, ((REFCLSID)ri)->Data3, ((REFCLSID)ri)->Data4[0],
		((REFCLSID)ri)->Data4[1], ((REFCLSID)ri)->Data4[2], ((REFCLSID)ri)->Data4[3],
		((REFCLSID)ri)->Data4[4], ((REFCLSID)ri)->Data4[5], ((REFCLSID)ri)->Data4[6],
		((REFCLSID)ri)->Data4[7]);
}


static int unregister_dll(void)
{
	HKEY		rootKey, hKey, hKey2;
	TCHAR		buffer[39];

	stringFromCLSID(&buffer[0], (REFCLSID)(&CLSID_IExample));

	// Open "HKEY_LOCAL_MACHINE\Software\Classes"
	if (!RegOpenKeyEx(HKEY_LOCAL_MACHINE, &ClassKeyName[0], 0, KEY_WRITE, &rootKey))
	{
		// Delete our CLSID key and everything under it
		if (!RegOpenKeyEx(rootKey, &CLSID_Str[0], 0, KEY_ALL_ACCESS, &hKey))
		{
			if (!RegOpenKeyEx(hKey, &buffer[0], 0, KEY_ALL_ACCESS, &hKey2))
			{
				RegDeleteKey(hKey2, &InprocServer32Name[0]);
				RegCloseKey(hKey2);
				RegDeleteKey(hKey, &buffer[0]);
			}
			RegCloseKey(hKey);
		}
		RegCloseKey(rootKey);
	}

	return 0;
}

int register_dll()
{
	int			result = -1;
	TCHAR		filename[MAX_PATH] = "IExample.dll";
	HKEY		rootKey, hKey, hKey2, hkExtra;
	TCHAR		buffer[39];
	DWORD		disposition;

	// Open "HKEY_LOCAL_MACHINE\Software\Classes"
	if (!RegOpenKeyEx(HKEY_LOCAL_MACHINE, &ClassKeyName[0], 0, KEY_WRITE, &rootKey))
	{
		// Open "HKEY_LOCAL_MACHINE\Software\Classes\CLSID"
		if (!RegOpenKeyEx(rootKey, &CLSID_Str[0], 0, KEY_ALL_ACCESS, &hKey))
		{
			stringFromCLSID(&buffer[0], (REFCLSID)(&CLSID_IExample));
			if (!RegCreateKeyEx(hKey, &buffer[0], 0, 0, REG_OPTION_NON_VOLATILE, KEY_WRITE, 0, &hKey2, &disposition))
			{
				RegSetValueEx(hKey2, 0, 0, REG_SZ, (const BYTE*)&ObjectDescription[0], sizeof(ObjectDescription));
				if (!RegCreateKeyEx(hKey2, &InprocServer32Name[0], 0, 0, REG_OPTION_NON_VOLATILE, KEY_WRITE, 0, &hkExtra, &disposition))
				{
					if (!RegSetValueEx(hkExtra, 0, 0, REG_SZ, (const BYTE*)&filename[0], lstrlen(&filename[0]) + 1))
					{
						if (!RegSetValueEx(hkExtra, &ThreadingModel[0], 0, REG_SZ, (const BYTE*)&BothStr[0], sizeof(BothStr)))
							result = 0;
					}
					RegCloseKey(hkExtra);
				}
				RegCloseKey(hKey2);
			}
			RegCloseKey(hKey);
		}
		RegCloseKey(rootKey);
	}
	
	if (result)
		unregister_dll();

	return result;
}

int main(int argc, char **argv)
{
	IExample        *exampleObj;
	IClassFactory	*classFactory;
	HRESULT	        hr;

	if (register_dll()) {
		printf("register failed\n");
		goto out;
	}

	if (!CoInitialize(0))
	{
		// Get IExample.DLL's IClassFactory
		if ((hr = CoGetClassObject(&CLSID_IExample, CLSCTX_INPROC_SERVER, 0, &IID_IClassFactory, &classFactory)))
			MessageBox(0, "Can't get IClassFactory", "CoGetClassObject error", MB_OK|MB_ICONEXCLAMATION);
		else
		{
			// Create an IExample object
			if ((hr = classFactory->lpVtbl->CreateInstance(classFactory, 0, &IID_IExample, &exampleObj)))
			{
				classFactory->lpVtbl->Release(classFactory);
				MessageBox(0, "Can't create IExample object", "CreateInstance error", MB_OK|MB_ICONEXCLAMATION);
			}
			else
			{
				char buffer[80];
				classFactory->lpVtbl->Release(classFactory);
				exampleObj->lpVtbl->SetString(exampleObj, "Hello world!");
				exampleObj->lpVtbl->GetString(exampleObj, buffer, sizeof(buffer));
				printf("string = %s (should be Hello World!)\n", buffer);
				exampleObj->lpVtbl->Release(exampleObj);
			}
		}
		CoUninitialize();
	}
	else
		MessageBox(0, "Can't initialize COM", "CoInitialize error", MB_OK|MB_ICONEXCLAMATION);

	if (unregister_dll())
		printf("unregister failed, maybe run as administrator\n");

out:
	system("pause");
}
