#include "system.h"


void panic(const char *error)
{
    if (error != NULL)
    {
        vga_clear(0x3);
        monitor_write(error);
    }

    for (;;);
}

