#include "../include/isr.h"
#include "../include/idt.h"

extern uint_32 isr1;

void isr_install()
{

}

extern "C" void isr_handler()
{
    //outb(0x20, 0x20);
    //outb(0xa0, 0x20);
}