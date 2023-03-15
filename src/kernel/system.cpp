#include "system.h"


void panic(const char *error)
{
    if (error != NULL)
    {
        clear(0x3);
        Font err_text; 
        err_text.setString(error);
        err_text.setColor(0xff);
        err_text.draw();
        swap_buffers();
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