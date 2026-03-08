#include "core.h"
#include <windows.h>

#define BARDLIB_IMPLEMENTATION
#include "bardlib.h"

#define deblog(x) MessageBoxA(global_state.win32.window, (x), "debug", 0)

bool on_line(int64_t idx, int64_t x1, int64_t y1, int64_t x2, int64_t y2)
{
    if (x1 == x2) {deblog("prevented div by zero lol?"); return false;}

    double slope = (double)(y1 - y2) / (double)(x1 - x2);
    // y = mx + b
    // y = slope * x + b;
    // b = (y1 - slope * x);
    int64_t constant = y1 - (int64_t)(slope * x1);
    int64_t idx_x = idx % global_state.window_width;
    int64_t idx_y = idx / global_state.window_height;
    bool satisfies_line = idx_y == (int64_t)((int64_t)(idx_x * slope) + constant);
    
    // TODO: assumes x2 > x1 and y2 > y1
    bool between_points_x = x1 <= idx_x && idx_x <= x2;
    bool between_points_y = y1 <= idx_y && idx_y <= y2; 

    return satisfies_line && between_points_x && between_points_y;
}

void bard_draw_line(uint64_t x1, uint64_t y1, uint64_t x2, uint64_t y2)
{
/*     uint64_t idx1 = y1 * global_state.window_width + x1;
    uint64_t idx2 = y2 * global_state.window_width + x2; */

    for (uint64_t idx = 0; idx < (global_state.window_width * global_state.window_height); ++idx)
    {
        if (on_line(idx, x1, y1, x2, y2)) {
            global_state.pixels[idx] = BARD_RGB(255, 0, 0);
        }
    }
};

int user_main()
{
    bard_create_window_win32(800, 600, "this is a title");

    while (!global_state.window_should_close)
    {
        bard_begin_drawing_win32();

        bard_draw_line(15, 15, 45, 45);

/*         for (int y = 0; y < global_state.window_height; y++)
        {
            for (int x = 0; x < global_state.window_width; x++) 
            {
                global_state.pixels[y * global_state.window_width + x] = BARD_RGB(255, 0, 0);
            }
        } */

        bard_end_drawing_win32();
    }
    return 0;
}