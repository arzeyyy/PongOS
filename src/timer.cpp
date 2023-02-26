#include "../include/timer.h"
#include "../include/Window/monitor.h"
#include "../include/isr.h"
#include "../include/irq.h"

// #define PIT_HZ 1193181
// #define DIV_OF_FREQ(_f) (PIT_HZ / (_f))
// #define FREQ_OF_DIV(_d) (PIT_HZ / (_d))

uint_32 tick = 0;

void timer_callback(registers_t regs)
{
    tick++;
    monitor_write("\nTick: ");
    monitor_write(toString(tick));
    monitor_write("\n");

}

void init_timer(uint_32 frequency)
{
    isr_install(IRQ0, timer_callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    uint_32 divisor = 1193180 / frequency;
    uint_8 low = (uint_8)(divisor & 0xFF);          // extract the lowest 8 bits of the divisor
    uint_8 high = (uint_8)((divisor >> 8) & 0xFF);  
    /* Send the command */
    outb(0x43, 0x36); /* Command port */
    outb(0x40, low);
    outb(0x40, high);
}

