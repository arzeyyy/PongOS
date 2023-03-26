#include "gfx.h"

//ball
void rect_draw(struct gfxRect *rect)
{
    if(rect->pos_x <= SCREEN_WIDTH && rect->pos_y <= SCREEN_HEIGHT)
    {
        for (int w = 0; w < rect->width; w++)
        {
            for (int h = 0; h < rect->height; h++)
            {
                vga_putc(w + rect->pos_x, h + rect->pos_y, rect->color);
            }
        }
    }
}
void rect_move(struct gfxRect *rect, int16_t x, int16_t y)
{
    rect->pos_x += x;
    rect->pos_y += y;
}

void rect_set_pos(struct gfxRect *rect, int16_t x, int16_t y)
{
    rect->pos_x = x;
    rect->pos_y = y;
};
