#pragma once

#include "../util.h"
#include "../Graphics/Font.h"
#include "../../src/drivers/vga.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4

/* Screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

/* Public kernel API */
void clear_screen();
void kprint_at(char *message, int col, int row);
void kprint(char *message);

void monitor_write(const char *s, uint_16 pos_x = 0, uint_16 pos_y = 0, uint_8 color = 0xff);
void monitor_clear();