/*
*  1. run as administrator
*  2. find service name : shift+R ¿é¤J services.msc
*  3. Double click service to get the real service name
*/

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

int main()
{
    TCHAR szSvcName[80] = TEXT("com.docker.service");
    SC_HANDLE schSCManager, schService;
    DWORD dwBytesNeeded, cbBufSize = 1000;
    LPQUERY_SERVICE_CONFIG lpsc = (LPQUERY_SERVICE_CONFIG)LocalAlloc(LMEM_FIXED, cbBufSize);
    LPSERVICE_DESCRIPTION lpsd = (LPSERVICE_DESCRIPTION)LocalAlloc(LMEM_FIXED, cbBufSize);
    SERVICE_DESCRIPTION sd;
    LPCWSTR szDesc = L"This is a test description";

    schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (!schSCManager)
    {
        printf("OpenSCManager failed (%d)\n", GetLastError());
        goto out;
    }

    // Get a handle to the service.
    schService = OpenService(schSCManager, szSvcName, SERVICE_QUERY_CONFIG);
    if (!schService)
    {
        printf("OpenService failed (%d)\n", GetLastError());
        CloseServiceHandle(schSCManager);
        goto out;
    }

    // Get the configuration information.
    if (!QueryServiceConfig(schService, lpsc, cbBufSize, &dwBytesNeeded))
    {
        printf("QueryServiceConfig failed (%d)", GetLastError());
        goto cleanup;
    }

    if (!QueryServiceConfig2(schService, SERVICE_CONFIG_DESCRIPTION, (LPBYTE)lpsd, cbBufSize, &dwBytesNeeded))
    {
        printf("QueryServiceConfig2 failed (%d)", GetLastError());
        goto cleanup;
    }

    if (!ChangeServiceConfig(
        schService,        // handle of service 
        SERVICE_NO_CHANGE, // service type: no change 
        SERVICE_DISABLED,  // service start type 
        SERVICE_NO_CHANGE, // error control: no change 
        NULL,              // binary path: no change 
        NULL,              // load order group: no change 
        NULL,              // tag ID: no change 
        NULL,              // dependencies: no change 
        NULL,              // account name: no change 
        NULL,              // password: no change 
        NULL))            // display name: no change
        printf("ChangeServiceConfig failed (%d)\n", GetLastError());
    else
        printf("Service disabled successfully.\n");


    /*sd.lpDescription = const_cast<LPWSTR>(szDesc);
    if (!ChangeServiceConfig2(
        schService,                 // handle to service
        SERVICE_CONFIG_DESCRIPTION, // change: description
        &sd))                      // new description
        printf("ChangeServiceConfig2 failed\n");
    else
        printf("Service description updated successfully.\n");*/

    /*if (!DeleteService(schService))
        printf("DeleteService failed (%d)\n", GetLastError());
    else
        printf("Service deleted successfully\n");*/


    // Print the configuration information.
    _tprintf(TEXT("%s configuration: \n"), szSvcName);
    _tprintf(TEXT("  Type: 0x%x\n"), lpsc->dwServiceType);
    _tprintf(TEXT("  Start Type: 0x%x\n"), lpsc->dwStartType);
    _tprintf(TEXT("  Error Control: 0x%x\n"), lpsc->dwErrorControl);
    _tprintf(TEXT("  Binary path: %s\n"), lpsc->lpBinaryPathName);
    _tprintf(TEXT("  Account: %s\n"), lpsc->lpServiceStartName);

    if (lpsd->lpDescription != NULL && lstrcmp(lpsd->lpDescription, TEXT("")) != 0)
        _tprintf(TEXT("  Description: %s\n"), lpsd->lpDescription);
    if (lpsc->lpLoadOrderGroup != NULL && lstrcmp(lpsc->lpLoadOrderGroup, TEXT("")) != 0)
        _tprintf(TEXT("  Load order group: %s\n"), lpsc->lpLoadOrderGroup);
    if (lpsc->dwTagId != 0)
        _tprintf(TEXT("  Tag ID: %d\n"), lpsc->dwTagId);
    if (lpsc->lpDependencies != NULL && lstrcmp(lpsc->lpDependencies, TEXT("")) != 0)
        _tprintf(TEXT("  Dependencies: %s\n"), lpsc->lpDependencies);

    LocalFree(lpsc);
    LocalFree(lpsd);

cleanup:
    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);

out:
    system("pause");
}
