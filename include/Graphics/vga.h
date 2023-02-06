#pragma once

#include "../util.h"


void set_video_mode(unsigned char mode);
void clear(uint_8 color = 0);
void draw_pixel(uint_16 x, uint_16 y, uint_8 color);
void draw_palette_tester();
void screen_init();

