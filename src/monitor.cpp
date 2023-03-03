#include "../include/Window/monitor.h"
#include "../include/timer.h"

// void setChar(char c, uint_16 pos_x, uint_16 pos_y, uint_8 color)
// {
//     if (c < 0 || c > 128)
//         return;

//     const uint_8 *glyph = FONT[(size_t)c]; // c is index to acces specific row in FONT

//     for (size_t yy = 0; yy < 8; yy++) // yy = whole line, columns
//     {
//         for (size_t xx = 0; xx < 8; xx++) // xx = 1 byte, rows
//         {
//             if (glyph[yy] & (1 << xx)) // (1 << xx), xx=2, bitwise left 00000001 = 00000100,
//             {
//                 draw_pixel(pos_x + xx, pos_y + yy, color);
//             }
//         }
//     }
// }
uint_16 current_line = 0;
uint_16 current_c = 0;

void monitor_write(const char *s, uint_16 pos_x, uint_16 pos_y, uint_8 color)
{
    uint_16 x = pos_x;
    uint_16 y = pos_y;
    x += (current_c * 8);
    y += (current_line * 8);

    char c;

    while ((c = *s++) != NULL) // (c = *s++) first, loop until character pointed to by s is a null terminator (0)
    {
        switch (c)
        {
        case NEW_LINE:
            current_line++;
            current_c = pos_x;
            x = pos_x;
            break;

        default:
            setChar(c, x, y, color);
            x += 8;
            current_c ++;
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

    // static uint_8 buffer[SCREEN_WIDTH];
    // for (int y = 0; y < SCREEN_HEIGHT; y++)
    // {
    //     // Copy a row of pixels from the current position to the buffer
    //     memcpy(buffer, (uint_8 *)(MEM_VGA + y * SCREEN_WIDTH), SCREEN_WIDTH);
    //     // Shift the pixels in the buffer one pixel to the left
    //     memmove(buffer, buffer + 1, SCREEN_WIDTH - 1);
    //     // Fill the empty space with new data
    //     buffer[SCREEN_WIDTH - 1] = (timer_get() + y) % 256;
    //     // Copy the updated row back to the screen
    //     memcpy((uint_8 *)(MEM_VGA + y * SCREEN_WIDTH), buffer, SCREEN_WIDTH);
    // }
}
// static void move_cursor()
// {
//     cursor_y = 0;
//     cursor_x = 0;

//     // The screen is 80 characters wide...
//     uint_16 cursorLocation = cursor_y * 80 + cursor_x;
//     outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
//     outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
//     outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
//     outb(0x3D5, cursorLocation);      // Send the low cursor byte.
// }

// static void scroll()
// {

//     // Get a space character with the default colour attributes.
//     uint_8 attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
//     uint_16 blank = 0x20 /* space */ | (attributeByte << 8);

//     // Row 25 is the end, this means we need to scroll up
//     if (cursor_y >= 25)
//     {
//         // Move the current text chunk that makes up the screen
//         // back in the buffer by a line
//         int i;
//         for (i = 0 * 80; i < 24 * 80; i++)
//         {
//             MEM_VGA[i] = MEM_VGA[i + 80];
//         }

//         // The last line should now be blank. Do this by writing
//         // 80 spaces to it.
//         for (i = 24 * 80; i < 25 * 80; i++)
//         {
//             MEM_VGA[i] = blank;
//         }
//         // The cursor should now be on the last line.
//         cursor_y = 24;
//     }
// }

void monitor_clear()
{
    clear();
}

