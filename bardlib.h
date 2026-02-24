#ifndef BARDLIB_H
#define BARDLIB_H

#include "windef.h" // IWYU pragma: keep
#include "winuser.h" // IWYU pragma: keep

#include <stdint.h> // IWYU pragma: keep
#include <stddef.h> // IWYU pragma: keep

typedef struct Window_State {
    union {
        struct { // win32
        HINSTANCE instance;
        WNDCLASS window_class;
        WNDPROC window_proc;
        HWND window;
        } win32;
    };
} Window_State;

void bard_window_create_win32(const char* window_title, WNDPROC window_proc);

#endif // BARDLIB_H
#ifdef BARDLIB_IMPLEMENTATION
// ##################################
// GLOBAL
// ##################################

Window_State global_window_state;

// ##################################
// FUNCTION DEFINITION
// ##################################

void bard_window_create_win32(const char* window_title, WNDPROC window_proc)
{
    HINSTANCE hinstance = GetModuleHandleA(NULL);

    const char* CLASS_NAME = window_title; // this doesn't determine title name

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc   = window_proc;
    wc.hInstance     = hinstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor       = LoadCursorA(NULL, IDC_ARROW); // first param is the location of the cursor resource

    RegisterClassA(&wc);

    HWND hwnd = CreateWindowExA(
        0,
        CLASS_NAME,
        window_title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hinstance, NULL
    );

    global_window_state.win32.instance = hinstance;
    global_window_state.win32.window_class = wc;
    global_window_state.win32.window = hwnd;
    global_window_state.win32.window_proc = window_proc;
}

#endif // BARDLIB_IMPLEMENTATION