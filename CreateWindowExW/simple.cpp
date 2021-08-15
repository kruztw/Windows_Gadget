// https://www.codegrepper.com/code-examples/cpp/c%2B%2B+create+window

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Title");

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[2][100] = { _T("Hello, 1!"), _T("Hello, 2!") };
    static int idx = 0;
    static HWND hWnd_EDIT = 0, hWnd_BUTTON = 0;
    HINSTANCE hInstance;

    switch (message)
    {
    case WM_CREATE:
        hInstance = (HINSTANCE)GetWindowLongPtrW(hWnd, GWLP_HINSTANCE);
        hWnd_EDIT = CreateWindowExW(0, L"EDIT", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, 5, 20, 400, 20, hWnd, NULL, hInstance, NULL);
        hWnd_BUTTON = CreateWindowExW(0, L"BUTTON", L"CLICK ME", WS_CHILD | WS_VISIBLE | WS_MAXIMIZEBOX | TME_HOVER, 5, 40, 400, 30, hWnd, NULL, hInstance, NULL);
        if (!hWnd_EDIT || !hWnd_BUTTON) {
            MessageBox(NULL, _T("failed"), _T("CreateWindowExW"), NULL);
            exit(0);
        }
        break;

    // https://blog.csdn.net/rankun1/article/details/50596634
    // WM_PAINT 由系統發送, 時機: 建立, 視窗大小變動 (e.g. 最小化, 伸縮 等等)
    // 下面 POC 透過 idx 證實結果
    case WM_PAINT: // Paint the main window
        hdc = BeginPaint(hWnd, &ps);
        TextOut(hdc, 5, 5, greeting[idx], _tcslen(greeting[idx]));
        EndPaint(hWnd, &ps);
        idx = (idx + 1) % 2;
        break;

    case WM_KEYDOWN:
        // 不論輸入小寫或大寫
        if (wParam == 'X')
            SetWindowTextW(hWnd_EDIT, L"You click x");
        else if (wParam == 'P')
            // 參考: https://iter01.com/551080.html
            PostMessageA(hWnd, 5278, 0, 0); // 發送訊息到 hWnd 介面, message: 5278 (可以想成 channel), wParam 和 lParam 都設成 NULL (請見 MSG 格式)
        else
            SetWindowTextW(hWnd, L"Title");
        break;

    case 5278:
        SetWindowTextW(hWnd, L"應該是從 main 的 DispatchMessage 轉發過來");
        break;

    // 按下 button 時會觸發, 如果沒設定 VM_COMMAND, 會直接 return DefWindowProc, 
    case WM_COMMAND:
        break;

    case WM_DESTROY: // post a quit message and return
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    if ((HWND)lParam == hWnd_BUTTON)
        SetWindowTextW(hWnd_EDIT, L"Button Clicked");

    return 0;
}

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL, _T("Call to RegisterClassEx failed!"), _T("Windows Desktop Guided Tour"), NULL);
        return 1;
    }

    HWND hWnd = CreateWindow(
        szWindowClass,                     // the name of the application
        szTitle,                           // the text that appears in the title bar
        WS_OVERLAPPEDWINDOW,               // the type of window to create
        CW_USEDEFAULT, CW_USEDEFAULT,      // initial position (x, y)
        500, 200,                          // initial size (width, length)
        NULL,                              // the parent of this window
        NULL,                              // this application does not have a menu bar
        hInstance,                         // the first parameter from WinMain
        NULL                               // not used in this application
    );

    if (!hWnd)
    {
        MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Windows Desktop Guided Tour"), NULL);
        return 1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))   // 消息可能來自系統, 或使用者 (PostMessage), 以 WM_USER (0x400) 為分界, 小於 => 系統專用
    {
        if (msg.message == 5278)
            MessageBox(NULL, _T("content"), _T("title"), NULL);

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
