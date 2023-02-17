#include "../include/system.h"

void panic(const char *error)
{
    if (error != NULL)
    clear(0x01);
    {
        err_text.setString(error);
    }

    for (;;)
    {
    }
}