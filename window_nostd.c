#include "bard_win32.h"

#define BARDLIB_IMPLEMENTATION
#include "bardlib.h"

bool on_line(int64_t idx, int64_t x1, int64_t y1, int64_t x2, int64_t y2)
{
    double slope = 0;

    if (x1 == x2) {
        slope = 1;
    } else {
        slope = (double)(y1 - y2) / (double)(x1 - x2);
    }

    // y = mx + b
    // y = slope * x + b;
    // b = (y1 - slope * x);
    int64_t constant = y1 - (int64_t)(slope * x1);
    int64_t idx_x = idx % global_state.window_width;
    int64_t idx_y = idx / global_state.window_height;
    bool satisfies_line = idx_y == (int64_t)((int64_t)(idx_x * slope) + constant);

    bool between_points_x = x2 > x1 ? x1 <= idx_x && idx_x <= x2 : x2 <= idx_x && idx_x <= x1;
    bool between_points_y = y2 > y1 ? y1 <= idx_y && idx_y <= y2 : y2 <= idx_y && idx_y <= y1;

    return satisfies_line && between_points_x && between_points_y;
}

void bard_draw_line(uint64_t x1, uint64_t y1, uint64_t x2, uint64_t y2, uint32_t color)
{
    uint64_t idx1 = y1 * global_state.window_width + x1;
    uint64_t idx2 = y2 * global_state.window_width + x2;

    if (idx1 == idx2) {global_state.pixels[idx1] = color; return;}

    uint64_t biggeridx = idx1 > idx2 ? idx1 : idx2;
    uint64_t smalleridx = idx1 < idx2 ? idx1 : idx2;

    if (biggeridx >= (global_state.window_height*global_state.window_width)) {return;}

    for (uint64_t idx = smalleridx; idx <= biggeridx; ++idx)
    {
        if (on_line(idx, x1, y1, x2, y2)) {
            global_state.pixels[idx] = color;
        }
    }
}

void bard_clear_background(uint32_t color)
{   // NOTE: global window width/height is more for rendering, they don't change during window resize
    // maybe making this const and local var will allow compiler to be smarter?
    const uint64_t windowsize = global_state.window_width * global_state.window_height;
    for (uint64_t idx = 0; idx < windowsize; ++idx) 
    {
        global_state.pixels[idx] = color;
    }
}

int user_main()
{
    printf_win32("is this flippin %s\n", "working");

    return 0;
    bard_create_window_win32(800, 600, "this is a title");

    while (!global_state.window_should_close)
    {
        bard_begin_drawing_win32();
        // bard_clear_background(BARD_RGB(255, 255, 255));

        // TODO this is incorrect, it also breaks at 800 600 for another incorrectness
        bard_draw_line(0, 0, 799, 599, BARD_RGB(255, 0, 0));

        bard_end_drawing_win32();
    }
    return 0;
}