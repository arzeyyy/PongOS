#pragma once

#include "../util.h"

class Font
{
private:
    uint_16 pos_x;
    uint_16 pos_y;

    uint_8 color;

    static const uint_8 a_font[128][8];

    
public:
    Font(/* args */);
    ~Font();

    void setPosition(uint_16 pos_x, uint_16 pos_y);
    void setColor(uint_8 color);
    void setChar(char c);
    void setString(const char *s);
};


