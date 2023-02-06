#include "../include/Text.h"

#define VGA_MEMORY (char *)0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// formating characters
#define NEW_LINE 10 // ASCII Line Feed
#define RETURN 13   // ASCII Carriage Return
#define NUL 0       // ASCII Null character

uint_16 cursorPos;

void Clear(uint_64 color = BACKGROUND_BLACK | FOREGROUND_WHITE)
{
  uint_64 value = 0;
  value += color << 8;
  value += color << 24;
  value += color << 40;
  value += color << 56;
  for (uint_64 *i = (uint_64 *)VGA_MEMORY; i < (uint_64 *)(VGA_MEMORY + 4000); i++) // loop through entire vga_memroy and fill it with color
  {
    *i = value;
  }
}

void SetCursorPosition(uint_16 pos)
{
  outb(0x3D4, 0x0F);
  outb(0x3D5, (uint_8)(pos & 0xFF));
  outb(0x3D4, 0x0E);
  outb(0x3D5, (uint_8)((pos >> 8) & 0xFF));

  uint_16 cursorPos = pos;
}

uint_16 PositionFromCords(uint_8 x, uint_8 y)
{
  return y * VGA_WIDTH + x;
}

void printf(const char *str, uint_8 color = FOREGROUND_WHITE | BACKGROUND_BLACK)
{
  uint_8 *charPtr = (uint_8 *)str;
  uint_16 index = cursorPos;
  while (*charPtr != NUL) // finished string
  {
    switch (*charPtr)
    {
    case NEW_LINE:
      index += VGA_WIDTH; //+80
      break;

    case RETURN:
      index = VGA_WIDTH;
      break;

    default:
      *(VGA_MEMORY + index * 2) = *charPtr;  // move character to cursor position, *2 because each character takes up 2 bytes(1 for character and 1 for color code)
      *(VGA_MEMORY + index * 2 + 1) = color; // set color
      index++;                               // cursor positon++
      break;
    }
    charPtr++;
  }
  SetCursorPosition(index);
}