#include "bard_win32.h"

#define BARDLIB_IMPLEMENTATION
#include "bardlib.h"

#define BARD_ABS(x) (x) <= 0 ? -(x) : (x)

bool idx_is_on_line(uint64_t idx, uint64_t x1, uint64_t y1, uint64_t x2, uint64_t y2)
{
    if (idx >= (global_state.window_height * global_state.window_width)) {printf_win32("WARNING: idx_is_on_line: idx too big \n)"); return false;}

    uint64_t idx_x = (uint64_t)(idx % global_state.window_width);
    uint64_t idx_y = (uint64_t)(idx / global_state.window_width);

    bool satisfies_y = false;
    bool satisfies_x = false;

    if (y1 == y2) {
        satisfies_y = idx_y == y1;
    } else {
        satisfies_y = y1 < y2 ? y1 <= idx_y && idx_y <= y2 : y2 <= idx_y && idx_y <= y1;
    }

    if (x1 == x2) {
        satisfies_x = idx_x == x1;
    } else {
        satisfies_x = x1 < x2 ? x1 <= idx_x && idx_x <= x2 : x2 <= idx_x && idx_x <= x1; 
    }

    // y = mx + n
    // m = (y1 - y2) / (x1 - x2)
    // n = y - mx
    double slope = x1 == x2 ? 1 : (double)(y1 - y2) / (double)(x1 - x2); // TODO: handle x1 == x2 case
    int64_t constant = y1 - slope * x1;

    bool satisfies_line = (idx_y == slope * idx_x + constant); // TODO: add tolerance level instead of exact match, thickness?

    return satisfies_x && satisfies_y && satisfies_line;
}

void bard_draw_line(uint64_t x1, uint64_t y1, uint64_t x2, uint64_t y2, uint32_t color)
{
    uint64_t idx1 = y1 * global_state.window_width + x1;
    uint64_t idx2 = y2 * global_state.window_width + x2;

    if (idx1 == idx2) {global_state.pixels[idx1] = color; printf_win32("WARNING: idx1 == idx2, coloring single pixel and exiting \n)"); return;}

    uint64_t biggeridx = idx1 > idx2 ? idx1 : idx2;
    uint64_t smalleridx = idx1 < idx2 ? idx1 : idx2;

    if (biggeridx >= (global_state.window_height * global_state.window_width)) {printf_win32("WARNING: biggeridx bigger than window :( \n)"); return;}

    for (uint64_t idx = smalleridx; idx <= biggeridx; ++idx)
    {
        if (idx_is_on_line(idx, x1, y1, x2, y2)) {
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
    constexpr uint64_t factor = 60;
    bard_create_window_win32(factor*16, factor*9, "this is a title");

    while (!global_state.window_should_close)
    {
        bard_begin_drawing_win32();
        bard_clear_background(BARD_RGB(255, 255, 255));

        // TODO this is incorrect, it also breaks at 800 600 for another incorrectness
        bard_draw_line(0, 0, factor*16 - 1, factor*9 - 1, BARD_RGB(255, 0, 0));

        bard_end_drawing_win32();
    }
    return 0;
}