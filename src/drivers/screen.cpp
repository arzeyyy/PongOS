#include "screen.h"

// VGA control port addresses
#define PALETTE_MASK 0x3C6
#define PALETTE_READ 0x3C7
#define PALETTE_WRITE 0x3C8
#define PALETTE_DATA 0x3C9

static uint_8 *BUFFER = (uint_8 *)0xA0000;

// double buffers
uint_8 buffers[SCREEN_SIZE];

uint_8 buff[2][SCREEN_SIZE];
uint_8 back = 0;

#define CURRENT (buff[back])
#define SWAP() (back = 1 - back)

void clear(uint_8 color)
{
  memset(CURRENT, color, SCREEN_SIZE);
}

// void screen_clear(uint_8 color)
// {
//   // filling vga graphics memory with 'color'
//   //memset(buffers, color, SCREEN_SIZE);
//   memset((char *)MEM_VGA, color, SCREEN_SIZE);
// }

void swap_buffers()
{
  memcpy(BUFFER, CURRENT, SCREEN_SIZE);
  //back = (1 - back);
  if(back == 0)
    back = 1;
  else if(back == 1)
    back = 0;
  //SWAP();
}

void draw_pixel(uint_16 x , uint_16 y, uint_8 color)
{
  uint_16 offset = y * SCREEN_WIDTH + x; // specifying position
  CURRENT[offset] = color;               // draw pixel on back buffer
  // uint_16 offset = y * SCREEN_WIDTH + x;  //specifying position
  // uint_8 *vram = (uint_8 *)MEM_VGA;       // points to single byte of memory, initialized in start of MEM_VGA
  // *(vram + offset) = color;               // vram + offset (vram[offset]) = color
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
  //memcpy(MEM_VGA, screen_buffer, sizeof(screen_buffer));
  memcpy(&CURRENT, screen_buffer, sizeof(screen_buffer));
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


static struct
{
  uint_16 line = 0;
  uint_16 c = 0;
} current;

void monitor_write(const char *s, uint_16 pos_x, uint_16 pos_y, uint_8 color)
{
  uint_16 x = pos_x;
  uint_16 y = pos_y;
  x += (current.c * 8);
  y += (current.line * 8);

  char c;

  // (c = *s++) first, loop until character pointed to by 's' is a null terminator (0)
  while ((c = *s++) != NULL) 
  {
    switch (c)
    {
    case NEW_LINE:
      current.line++;
      current.c = 0;
      x = pos_x;
      break;

    default:
      setChar(c, x, y, color);
      x += 8;
      current.c++;
      break;
    }
  }
}

void scroll_screen()
{
  for (size_t i = 0; i < SCREEN_HEIGHT; i++)
  {
    memset((uint_8 *)MEM_VGA + (i * SCREEN_WIDTH), (timer_get() - i) % 256, SCREEN_WIDTH);
  }
}
