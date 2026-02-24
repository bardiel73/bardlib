
#include "core.h"

#define BARDLIB_IMPLEMENTATION
#include "bardlib.h"

#define BARD_BITSET(val, index) val = (uint64_t)((val) | (uint64_t)((uint64_t)1 << (index)))
#define BARD_BITUNSET(val, index) val = (uint64_t)((val) & (uint64_t)((uint64_t)0 << (index)))
#define BARD_BITTEST(val, index) (uint64_t)((val) & (uint64_t)((uint64_t)1 << (index)))

#define LAST_ASCII ('Z' - 65)
#define BARD_ESC (LAST_ASCII + 1)

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
            switch(wParam)
            {
                case 'A': BARD_BITSET(global_state.keyboard, 'A' - 65); break;
                case 'B': BARD_BITSET(global_state.keyboard, 'B' - 65); break;
                case 'C': BARD_BITSET(global_state.keyboard, 'C' - 65); break;
                case 'D': BARD_BITSET(global_state.keyboard, 'D' - 65); break;
                case 'E': BARD_BITSET(global_state.keyboard, 'E' - 65); break;
                case 'F': BARD_BITSET(global_state.keyboard, 'F' - 65); break;
                case 'G': BARD_BITSET(global_state.keyboard, 'G' - 65); break;
                case 'H': BARD_BITSET(global_state.keyboard, 'H' - 65); break;
                case 'I': BARD_BITSET(global_state.keyboard, 'I' - 65); break;
                case 'J': BARD_BITSET(global_state.keyboard, 'J' - 65); break;
                case 'K': BARD_BITSET(global_state.keyboard, 'K' - 65); break;
                case 'L': BARD_BITSET(global_state.keyboard, 'L' - 65); break;
                case 'M': BARD_BITSET(global_state.keyboard, 'M' - 65); break;
                case 'N': BARD_BITSET(global_state.keyboard, 'N' - 65); break;
                case 'O': BARD_BITSET(global_state.keyboard, 'O' - 65); break;
                case 'P': BARD_BITSET(global_state.keyboard, 'P' - 65); break;
                case 'Q': BARD_BITSET(global_state.keyboard, 'Q' - 65); break;
                case 'R': BARD_BITSET(global_state.keyboard, 'R' - 65); break;
                case 'S': BARD_BITSET(global_state.keyboard, 'S' - 65); break;
                case 'T': BARD_BITSET(global_state.keyboard, 'T' - 65); break;
                case 'U': BARD_BITSET(global_state.keyboard, 'U' - 65); break;
                case 'V': BARD_BITSET(global_state.keyboard, 'V' - 65); break;
                case 'W': BARD_BITSET(global_state.keyboard, 'W' - 65); break;
                case 'X': BARD_BITSET(global_state.keyboard, 'X' - 65); break;
                case 'Y': BARD_BITSET(global_state.keyboard, 'Y' - 65); break;
                case 'Z': BARD_BITSET(global_state.keyboard, 'Z' - 65); break;
                case VK_ESCAPE: BARD_BITSET(global_state.keyboard, BARD_ESC); DestroyWindow(hwnd); break;
            }
        } break;

        case WM_KEYUP: {
            switch(wParam)
            {
                case 'A': BARD_BITUNSET(global_state.keyboard, 'A' - 65); break;
                case 'B': BARD_BITUNSET(global_state.keyboard, 'B' - 65); break;
                case 'C': BARD_BITUNSET(global_state.keyboard, 'C' - 65); break;
                case 'D': BARD_BITUNSET(global_state.keyboard, 'D' - 65); break;
                case 'E': BARD_BITUNSET(global_state.keyboard, 'E' - 65); break;
                case 'F': BARD_BITUNSET(global_state.keyboard, 'F' - 65); break;
                case 'G': BARD_BITUNSET(global_state.keyboard, 'G' - 65); break;
                case 'H': BARD_BITUNSET(global_state.keyboard, 'H' - 65); break;
                case 'I': BARD_BITUNSET(global_state.keyboard, 'I' - 65); break;
                case 'J': BARD_BITUNSET(global_state.keyboard, 'J' - 65); break;
                case 'K': BARD_BITUNSET(global_state.keyboard, 'K' - 65); break;
                case 'L': BARD_BITUNSET(global_state.keyboard, 'L' - 65); break;
                case 'M': BARD_BITUNSET(global_state.keyboard, 'M' - 65); break;
                case 'N': BARD_BITUNSET(global_state.keyboard, 'N' - 65); break;
                case 'O': BARD_BITUNSET(global_state.keyboard, 'O' - 65); break;
                case 'P': BARD_BITUNSET(global_state.keyboard, 'P' - 65); break;
                case 'Q': BARD_BITUNSET(global_state.keyboard, 'Q' - 65); break;
                case 'R': BARD_BITUNSET(global_state.keyboard, 'R' - 65); break;
                case 'S': BARD_BITUNSET(global_state.keyboard, 'S' - 65); break;
                case 'T': BARD_BITUNSET(global_state.keyboard, 'T' - 65); break;
                case 'U': BARD_BITUNSET(global_state.keyboard, 'U' - 65); break;
                case 'V': BARD_BITUNSET(global_state.keyboard, 'V' - 65); break;
                case 'W': BARD_BITUNSET(global_state.keyboard, 'W' - 65); break;
                case 'X': BARD_BITUNSET(global_state.keyboard, 'X' - 65); break;
                case 'Y': BARD_BITUNSET(global_state.keyboard, 'Y' - 65); break;
                case 'Z': BARD_BITUNSET(global_state.keyboard, 'Z' - 65); break;
                case VK_ESCAPE: BARD_BITUNSET(global_state.keyboard, BARD_ESC); break;
            }
        } break;

        case WM_KILLFOCUS: global_state.keyboard = 0; break;

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
            global_state.window_should_close = true;
        }

        TranslateMessage(&msg);
        DispatchMessageA(&msg); // calls WindowProc
    }
}

int user_main()
{
    bard_window_create_win32("this is a title", WindowProc);

    while (!global_state.window_should_close)
    {
        bard_poll_events();
    }

    return 0;
}