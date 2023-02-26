#include "vga.h"

// VGA control port addresses
#define PALETTE_MASK 0x3C6
#define PALETTE_READ 0x3C7
#define PALETTE_WRITE 0x3C8
#define PALETTE_DATA 0x3C9

void clear(uint_8 color)
{
  // filling vga graphics memory with 'color', 64000=size of vga graphics memory
  memset((char *)MEM_VGA, color, 64000); 
}

void draw_pixel(uint_16 x , uint_16 y, uint_8 color)
{
  uint_16 offset = y * SCREEN_WIDTH + x;  //specifying position
  uint_8 *vram = (uint_8 *)MEM_VGA;       // points to single byte of memory, initialized in start of MEM_VGA
  *(vram + offset) = color;               // vram + offset, vram[offset] = color
}

uint_8 screen_buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
void draw_palette_tester() 
{
  for (int y = 0; y < SCREEN_HEIGHT; y++) {             //columns
    for (int x = 0; x < SCREEN_WIDTH; x++) {            //rows
      screen_buffer[y][x] = y / (SCREEN_WIDTH / 256);   //generate color, 199 / 1.25 = 159
    }
  }

  // Write the color from screen_buffer to vga memory
  memcpy(MEM_VGA, screen_buffer, sizeof(screen_buffer));
}

void screen_init() {
  // 8-bit RRRGGGBB
  outb(PALETTE_MASK, 0xFF); // enable all bits for update
  outb(PALETTE_WRITE, 0);   // update first entry
  for (uint_8 i = 0; i < 255; i++)
  {
    outb(PALETTE_DATA, (((i >> 5) & 0x7) * (256 / 8)) / 4); // extract red   11111110 >> 5 = 00000111, last 3 red   & 0x7 = 00000111
    outb(PALETTE_DATA, (((i >> 2) & 0x7) * (256 / 8)) / 4); // extract green 11111110 >> 2 = 00111111, last 3 green & 0x7 = 00000111
    outb(PALETTE_DATA, (((i >> 0) & 0x3) * (256 / 4)) / 4); // extract blue  11111110 >> 0 = 11111110, last 2 blue  & 0x3 = 00000010
    // 7 * 32 = 224, 224 / 4 = 56, range 0 - 56
  }
  // set color 255 = white
  outb(PALETTE_DATA, 0x3F);
  outb(PALETTE_DATA, 0x3F);
  outb(PALETTE_DATA, 0x3F);
}

