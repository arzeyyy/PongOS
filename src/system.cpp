#include "../include/system.h"

void panic(const char *error)
{
    if (error != NULL)
    clear(0x01);
    {  
        Font err_text; 
        err_text.setString(error);
    }

    for (;;)
    {
    }
}