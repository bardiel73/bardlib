
#include "core.h"

#define BARDLIB_IMPLEMENTATION
#include "bardlib.h"

void animate_pixels(int x_offset, int y_offset)
{
    #define bard_RGB(r, g, b) (uint32_t)((r << 16) | (g << 8) | b)

    for (int y = 0; y < global_state.window_height; y++) {
        for (int x = 0; x < global_state.window_width; x++) {
            uint8_t r = (uint8_t)(x + x_offset);
            uint8_t g = (uint8_t)(y + y_offset);
            uint8_t b = 255;

            global_state.pixels[y * global_state.window_width + x] = bard_RGB(r, g, b);
        }
    }
}

int user_main()
{
    bard_create_window_win32(800, 600, "this is a title");

    while (!global_state.window_should_close)
    {
        bard_begin_drawing_win32();

        for (int y = 0; y < global_state.window_height; y++) {
            for (int x = 0; x < global_state.window_width; x++) {
                global_state.pixels_BGRA[y * global_state.window_width + x].r = 255;
                global_state.pixels_BGRA[y * global_state.window_width + x].g = 0;
                global_state.pixels_BGRA[y * global_state.window_width + x].b = 255;
                global_state.pixels_BGRA[y * global_state.window_width + x].a = 0;
            }
        }

        bard_end_drawing_win32();
    }

    return 0;
}