
#include "core.h"

#define BARDLIB_IMPLEMENTATION
#include "bardlib.h"

uint8_t esc_is_pressed = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE: { // user attempted to close the window
            DestroyWindow(hwnd);
        } break;

        case WM_DESTROY: { // the closed window's resources are getting released
            // thread is quiting (sends WM_QUIT, not handled by windproc, used to exit the inf loop in main)
            PostQuitMessage(0); 
        } break;

        case WM_KEYDOWN: { // https://learn.microsoft.com/en-gb/windows/win32/inputdev/virtual-key-codes
            if (wParam == VK_ESCAPE)
            {
                esc_is_pressed = 1;
                DestroyWindow(hwnd);
            } 
        } break;

        case WM_KEYUP: {
            if (wParam == VK_ESCAPE)
            {
                esc_is_pressed = 0;
            } 
        } break;


        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            // All painting happens here...
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
        } break;

        default: {
            return DefWindowProcA(hwnd, uMsg, wParam, lParam);
        } break;
    }
    return 0;
}

void bard_poll_events()
{
    MSG msg = {0};

    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT) {
            global_window_state.win32.window_should_close = true;
        }

        TranslateMessage(&msg);
        DispatchMessageA(&msg); // calls WindowProc
    }
}

int user_main()
{
    bard_window_create_win32("this is a title", WindowProc);

    while (!global_window_state.win32.window_should_close)
    {
        bard_poll_events();
    }

    return 0;
}