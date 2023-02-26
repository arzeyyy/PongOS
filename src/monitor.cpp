#include "../include/Window/monitor.h"


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

void monitor_write(const char *s, uint_16 pos_x, uint_16 pos_y, uint_8 color)
{
    uint_16 init_x = pos_x;
    uint_16 init_y = pos_y;

    char c;

    while ((c = *s++) != NULL) // (c = *s++) first, loop until character pointed to by s is a null terminator (0)
    {
        switch (c)
        {
        case NEW_LINE:
            pos_y += 8;
            pos_x = init_x;
            break;

        default:
            setChar(c, pos_x, pos_y, color);
            pos_x += 8;
            break;
        }
    }
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

