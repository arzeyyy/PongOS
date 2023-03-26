#ifndef VGA_H
#define VGA_H

#include "../kernel/util.h"
#include "timer.h"
#include "../kernel/Font.h"

static uint_8 *vga_addr = (uint_8 *)0xA0000;

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)

void vga_init();
void vga_clear(uint_8 color = 0);
void vga_swap();
void vga_putc(uint_16 x, uint_16 y, uint_8 color);
char vga_getc(uint_16 x, uint_16 y);

void draw_palette_tester();
void monitor_write(const char *s, uint_16 pos_x = 0, uint_16 pos_y = 0, uint_8 color = 0xff);


#endif
