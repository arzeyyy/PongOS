#pragma once
#include "util.h"
#include "../drivers/screen.h"

class Rect
{
private:
    uint_16 pos_x;
    uint_16 pos_y;

    uint_16 width;
    uint_16 height;

    uint_8 color;

public:
    Rect()
    {
        pos_x = 0;
        pos_y = 0;

        width = 0;
        height = 0;

        color = 0xFF;
    }

    ~Rect() {}

    void setPosition(uint_16 pos_x, uint_16 pos_y)
    {
        this->pos_x = pos_x;
        this->pos_y = pos_y;
    }

    uint_16 getPosition()
    {
        return pos_x, pos_y;
    }

    void setSize(uint_16 width, uint_16 height)
    {
        this->width = width;
        this->height = height;
    }


    uint_16 getSize()
    {
        return width, height;
    }

    void setColor(uint_8 color)
    {
        this->color = color;
    }

    uint_16 getColor()
    {
        return color;
    }

    void move(uint_8 x, uint_8 y)
    {
        pos_x += x;
        pos_y += y;
    }

    void draw()
    {
        for (uint_16 i = pos_x; i < pos_x + width; i++)
        {
            for (uint_16 j = pos_y; j < pos_y + height; j++)
            {
                draw_pixel(i, j, color);
            }
        }
    }
};