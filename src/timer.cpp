#include "../include/timer.h"
#include "../include/Graphics/Font.h"
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

    //Firstly, register our timer callback.
    isr_install(IRQ0, &timer_callback);


    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    uint_32 divisor = 1193180 / frequency;

    // Send the command byte.
    outb(0x43, 0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    uint_8 l = (uint_8)(divisor & 0xFF);
    uint_8 h = (uint_8)((divisor >> 8) & 0xFF);

    // Send the frequency divisor.
    outb(0x40, l);
    outb(0x40, h);
}

