#ifndef SCREEN_H
#define SCREEN_H

#include "../kernel/util.h"
#include "timer.h"
#include "../kernel/Font.h"

#define MEM_VGA (char *)0xA0000
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)

// extern uint_16 buffers[2][SCREEN_SIZE];
// extern uint_8 back;

void set_video_mode(unsigned char mode);
void screen_clear(uint_8 color = 0);
void draw_pixel(uint_16 x, uint_16 y, uint_8 color);
void draw_palette_tester();
void screen_init();
void swap_buffers();
void monitor_write(const char *s, uint_16 pos_x = 0, uint_16 pos_y = 0, uint_8 color = 0xff);
void scroll_screen();
void clear(uint_8 color = 0);

#endif
