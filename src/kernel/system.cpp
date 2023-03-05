#include "system.h"


void panic(const char *error)
{
    if (error != NULL)
    {
        screen_clear(0x3);
        Font err_text; 
        err_text.setString(error);
        err_text.setColor(0xff);
        err_text.draw();
    }

    for (;;);
}