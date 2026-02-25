#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define BARD_RGB(r, g, b) (uint32_t)((0x00 << 24) | (((uint8_t)(r)) << 16) | (((uint8_t)(g)) << 8) | ((uint8_t)(b)))

#define R_RGB(rgb) (uint8_t)(((rgb) >> 16) & 0xFF)
#define G_RGB(rgb) (uint8_t)(((rgb) >> 8) & 0xFF)
#define B_RGB(rgb) (uint8_t)((rgb) & 0xFF)

#define BARD_MIN(x_, y_) ((x_) <= (y_) ? (x_) : (y_))
#define BARD_MAX(x_, y_) ((x_) >= (y_) ? (x_) : (y_))
#define BARD_CLAMP(value_, minimum_, maximum_) BARD_MAX(minimum_, BARD_MIN(value_, maximum_))

uint32_t bard_hsv_to_rgb(uint32_t h, float s, float v)
{
    h = h % 360;
    s = BARD_CLAMP(s, 0.0f, 1.0f);
    v = BARD_CLAMP(v, 0.0f, 1.0f);

    float C = v * s;
    float h1 = h / 60.0f;
    // X = C * (1 - abs(h1 mod 2 - 1))
    float X = C * (1.0f - fabsf(fmodf(h1, 2) - 1.0f));
    
    float r1 = 0, g1 = 0, b1 = 0;

    if      (h1 >= 0 && h1 < 1) { r1 = C; g1 = X; b1 = 0; }
    else if (h1 >= 1 && h1 < 2) { r1 = X; g1 = C; b1 = 0; }
    else if (h1 >= 2 && h1 < 3) { r1 = 0; g1 = C; b1 = X; }
    else if (h1 >= 3 && h1 < 4) { r1 = 0; g1 = X; b1 = C; }
    else if (h1 >= 4 && h1 < 5) { r1 = X; g1 = 0; b1 = C; }
    else if (h1 >= 5 && h1 < 6) { r1 = C; g1 = 0; b1 = X; }

    float m = v - C;

    uint8_t r2 = (uint8_t)((r1 + m) * 255.0f + 0.5f);
    uint8_t g2 = (uint8_t)((g1 + m) * 255.0f + 0.5f);
    uint8_t b2 = (uint8_t)((b1 + m) * 255.0f + 0.5f);
    
    return BARD_RGB(r2, g2, b2);
}

int main()
{
    int r = 255;
    int g = 0;
    int b = 0;
    printf("r=%d, g=%d, b=%d\n", r, g, b);
    uint32_t hsv = bard_hsv_to_rgb(120, 1, 1);
    printf("r=%d, g=%d, b=%d\n", R_RGB(hsv), G_RGB(hsv), B_RGB(hsv));
}