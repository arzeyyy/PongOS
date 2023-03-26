#ifndef GFX_h
#define GFX_H

#include "util.h"
#include "../drivers/vga.h"

struct gfxRect
{
    int16_t width, height, pos_x, pos_y;
    uint_8 color;
    int16_t speed_x, speed_y;
    
};

void rect_draw(struct gfxRect *rect);
void rect_move(struct gfxRect *rect, int16_t x, int16_t y);
void rect_set_pos(struct gfxRect *rect, int16_t x, int16_t y);

#endif