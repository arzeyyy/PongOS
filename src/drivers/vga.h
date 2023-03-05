#ifndef VGA_H
#define VGA_H

#include "../../include/util.h"

#define MEM_VGA (char *)0xA0000
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)

void set_video_mode(unsigned char mode);
void clear(uint_8 color = 0);
void draw_pixel(uint_16 x, uint_16 y, uint_8 color);
void draw_palette_tester();
void screen_init();
void screen_swap();

#endif