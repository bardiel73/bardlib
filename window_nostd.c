
#include "core.h"

#define BARDLIB_IMPLEMENTATION
#include "bardlib.h"

int user_main()
{
    bard_create_window_win32(800, 600, "this is a title");

    while (!global_state.window_should_close)
    {
        bard_begin_drawing_win32();

        for (int y = 0; y < global_state.window_height; y++)
        {
            for (int x = 0; x < global_state.window_width; x++) 
            {
                global_state.pixels_BGRA[y * global_state.window_width + x].r = 255;
                global_state.pixels_BGRA[y * global_state.window_width + x].g = 0;
                global_state.pixels_BGRA[y * global_state.window_width + x].b = 255;
            }
        }

        bard_end_drawing_win32();
    }
    return 0;
}