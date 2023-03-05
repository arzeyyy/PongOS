#include "timer.h"


#define PIT_HZ 1193180

static struct
{
    uint_64 divisor;
    uint_64 ticks;
    uint_32 freq;
} state;

void print_ticks()
{
    monitor_write("Tick: ");
    monitor_write(to_string(state.ticks));
    monitor_write("\n");
}

void timer_callback(registers_t regs)
{
    state.ticks++;
    //print_ticks();
}

uint_64 timer_get()
{
    return state.ticks; 
}

void sleep(uint_64 milliseconds)
{
    uint_32 end = state.ticks + milliseconds * state.freq;
    while (state.ticks < end);
}

void timer_init(uint_32 frequency)
{
    state.freq = frequency;
    state.ticks = 0;
    isr_install(IRQ0, timer_callback);

    /* hardware clock at 1193180 Hz*/
    state.divisor = PIT_HZ / frequency;
    uint_8 low = (uint_8)(state.divisor & 0xFF); // extract the lowest 8 bits of the divisor
    uint_8 high = (uint_8)((state.divisor >> 8) & 0xFF);

    /* Send the command */
    outb(0x43, 0x36); // Command register port
    outb(0x40, low);  // Channel 0 data port
    outb(0x40, high); // Channel 0 data port
}

