
#include "core.h"

#define BARDLIB_IMPLEMENTATION
#include "bardlib.h"

static inline uint32_t MakePixel(uint8_t r, uint8_t g, uint8_t b) {
    return 0xFF000000 | (r << 16) | (g << 8) | b;
}

void RenderSoftware(int x_offset, int y_offset) {
    for (int y = 0; y < global_state.window_height; y++) {
        for (int x = 0; x < global_state.window_width; x++) {
            uint8_t r = (uint8_t)(x + x_offset);
            uint8_t g = (uint8_t)(y + y_offset);
            uint8_t b = 0;

            global_state.pixels[y * global_state.window_width + x] = MakePixel(r, g, b);
        }
    }
}

int user_main()
{
    bard_create_window_win32(800, 600, "this is a title");

    uint16_t x = 0;
    uint16_t y = 0;

    while (!global_state.window_should_close)
    {
        bard_begin_drawing_win32();

        RenderSoftware(x++, y++);

        bard_end_drawing_win32();
    }

    return 0;
}