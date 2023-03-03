#pragma once

#include "../util.h"
#include "../Graphics/Font.h"
#include "../../src/drivers/vga.h"

void clear_screen();
void monitor_write(const char *s, uint_16 pos_x = 0, uint_16 pos_y = 0, uint_8 color = 0xff);
void monitor_clear();
void scroll_screen();