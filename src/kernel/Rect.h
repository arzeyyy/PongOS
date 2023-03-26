#pragma once
#include "util.h"
#include "../drivers/vga.h"

class Rect
{
private:
    int16_t pos_x;
    int16_t pos_y;

    int16_t width;
    int16_t height;

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

    struct Dimensions
    {
        int16_t x;
        int16_t y;
    };

    void setPosition(int16_t pos_x, int16_t pos_y)
    {
        this->pos_x = pos_x;
        this->pos_y = pos_y;
    }

    Dimensions getPosition() const
    {
        return {pos_x, pos_y};
    }

    void setSize(int16_t width, int16_t height)
    {
        this->width = width;
        this->height = height;
    }

    Dimensions getSize()
    {
        return {width, height};
    }

    void setColor(uint_8 color)
    {
        this->color = color;
    }

    uint_16 getColor()
    {
        return color;
    }

    void move(int16_t x, int16_t y)
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
                vga_putc(i, j, color);
            }
        }
    }
};