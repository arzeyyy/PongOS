#pragma once

#include "util.h"
#include "../drivers/vga.h"

#define NEW_LINE 10


//void monitor_write(const char *s, uint_16 pos_x = 0, uint_16 pos_y = 0, uint_8 color = 0xff);

void setChar(uint_8 c, uint_16 pos_x, uint_16 pos_y, uint_8 color);
void font_draw(const char *s, uint_16 pos_x = 0, uint_16 pos_y = 0, uint_8 color = 0xff);

// class Font
// {
// private:
//     uint_16 init_x;
//     uint_16 init_y;

//     uint_16 pos_x;
//     uint_16 pos_y;

//     uint_8 color;

//     char *string;

//     uint_16 width;
//     uint_16 height;
    
//     static const uint_8 a_font[128][8];

//     void setChar(uint_8 c);

// public:
//     Font(/* args */);
//     ~Font();

//     void setPosition(uint_16 pos_x, uint_16 pos_y);
//     void setColor(uint_8 color);
//     void setString(const char *s);
//     void setOrigin(uint_16 x, uint_16 y);
//     void draw();

//     struct Bounds
//     {
//         int width;
//         int height;
//     };

//     Bounds getLocalBounds() const;
// };


