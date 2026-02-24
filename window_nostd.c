
#include "core.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            // All painting happens here...
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
            return 0;
        }
        default:
        {
            return DefWindowProcA(hwnd, uMsg, wParam, lParam);
        }
    }
}

int user_main()
{
    HINSTANCE instance_handle = GetModuleHandleA(NULL);
    const char* CLASS_NAME = "main_window_class_name";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = instance_handle;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor       = LoadCursorA(NULL, IDC_ARROW); // first param is the location of the cursor resource

    RegisterClassA(&wc);

    HWND hwnd = CreateWindowExA(
        0,
        CLASS_NAME,
        "window_title",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, instance_handle, NULL
    );

    ShowWindow(hwnd, SW_NORMAL);

    MSG msg = {0};
    BOOL bRet;
    while( (bRet = GetMessageA( &msg, NULL, 0, 0 )) != 0)
    { 
        if (bRet == -1) {return -1;}

        TranslateMessage(&msg); 
        DispatchMessageA(&msg); 
    }

    return 0;
}