
#include "core.h"

#define BARDLIB_IMPLEMENTATION
#include "bardlib.h"

#define BARD_RGB(r, g, b) (uint32_t)((0x00 << 24) | (((uint8_t)(r)) << 16) | (((uint8_t)(g)) << 8) | ((uint8_t)(b)))

#define R_RGB(rgb) (uint8_t)(((rgb) >> 16) & 0xFF)
#define G_RGB(rgb) (uint8_t)(((rgb) >> 8) & 0xFF)
#define B_RGB(rgb) (uint8_t)((rgb) & 0xFF)

#define BARD_MIN(x_, y_) ((x_) <= (y_) ? (x_) : (y_))
#define BARD_MAX(x_, y_) ((x_) >= (y_) ? (x_) : (y_))
#define BARD_CLAMP(value_, minimum_, maximum_) BARD_MAX(minimum_, BARD_MIN(value_, maximum_))

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
                global_state.pixels[y * global_state.window_width + x] = BARD_RGB(255, 0, 0);
            }
        }

        bard_end_drawing_win32();
    }
    return 0;
}