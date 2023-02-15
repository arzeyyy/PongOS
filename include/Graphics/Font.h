#pragma once

#include "../util.h"
#include "vga.h"

#define NEW_LINE 10
#define NULL 0


class Font
{
private:
    uint_16 init_x;
    uint_16 init_y;

    uint_16 pos_x;
    uint_16 pos_y;

    uint_8 color;

    char *string;

    uint_16 width;
    uint_16 height;
    
    static const uint_8 a_font[128][8];


    void setChar(char c);

public:
    Font(/* args */);
    ~Font();

    void setPosition(uint_16 pos_x, uint_16 pos_y);
    void setColor(uint_8 color);
    void setString(const char *s);
    void setOrigin(uint_16 x, uint_16 y);
    void draw();

    struct Bounds
    {
        int width;
        int height;
    };

    Bounds getLocalBounds() const;
};


