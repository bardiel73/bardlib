
#include "core.h"

#define BARDLIB_IMPLEMENTATION
#include "bardlib.h"

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
    bard_win32_window_create("this is a title", WindowProc);

    ShowWindow(global_window_state.window, SW_NORMAL);

    MSG msg = {0};
    BOOL bRet;
    while( (bRet = GetMessageA( &msg, NULL, 0, 0 )) != 0)
    { 
        if (bRet == -1) {return -1;}

        TranslateMessage(&msg); DispatchMessageA(&msg); 
    }

    return msg.wParam;
}