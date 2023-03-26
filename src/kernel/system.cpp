#include "system.h"


void panic(const char *error)
{
    if (error != NULL)
    {
        vga_clear(0x3);
        monitor_write(error);
        // Font err_text; 
        // err_text.setString(error);
        // err_text.setColor(0xff);
        // err_text.draw();
        //vga_swap();
    }

    for (;;);
}

uint_64 last_tick;
void init_system()
{
    last_tick = timer_get();
}

float get_delta_time()
{
    uint_64 curr_tick = timer_get();
    float delta_time = (curr_tick / last_tick) / (float)state.freq;
    last_tick = curr_tick;
    return delta_time;
}