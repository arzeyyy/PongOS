#pragma once

#include "util.h"
#include "TextColorCodes.h"

//unsigned short cursorPos;

extern void SetCursorPosition(unsigned short pos);
extern void Clear(uint_64 color);
extern void printf(const char *str, uint_8 color);
unsigned short PositionFromCords(unsigned char x, unsigned char y);

