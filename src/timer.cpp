#include "../include/timer.h"
#include "../include/Window/monitor.h"
#include "../include/isr.h"
#include "../include/irq.h"

#define PIT_HZ 1193180
// #define DIV_OF_FREQ(_f) (PIT_HZ / (_f))
// #define FREQ_OF_DIV(_d) (PIT_HZ / (_d))

static struct
{
    uint_64 divisor;
    uint_64 tick;
} state;

void print_ticks()
{
    monitor_write("Tick: ");
    monitor_write(toString(state.tick));
    monitor_write("\n");
}

void timer_callback(registers_t regs)
{
    state.tick++;
    print_ticks();
}

uint_64 timer_get()
{
    return state.tick; 
}

void init_timer(uint_32 frequency)
{
    state.tick = 0;
    isr_install(IRQ0, timer_callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    state.divisor = PIT_HZ / frequency;
    uint_8 low = (uint_8)(state.divisor & 0xFF); // extract the lowest 8 bits of the divisor
    uint_8 high = (uint_8)((state.divisor >> 8) & 0xFF);
    /* Send the command */
    outb(0x43, 0x36); // Command register port
    outb(0x40, low);  // Channel 0 data port
    outb(0x40, high); // Channel 0 data port
}

