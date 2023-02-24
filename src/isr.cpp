#include "../include/isr.h"
#include "../include/idt.h"
#include "../include/system.h"

#define NUM_ISRS 48
#define NUM_INTS 256

// extern "C" void isr0(struct Registers *);
// extern "C" void isr1(struct Registers *);
// extern "C" void isr2(struct Registers *);

const char *exceptions[] = {
    "Division By Zero exception",
    "Debug exception",
    "Non Maskable Interrupt",
    "Breakpoint exception",
    "Into Detected Overflow",
    "Out of Bounds exception",
    "Invalid Opcode exception",
    "No Coprocessor exception",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt exception",
    "Coprocessor Fault",
    "Alignment Check exception",
    "Machine Check exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};

isr_t handlers[256];

void isr_install(uint_8 n, isr_t handler)
{
    handlers[n] = handler;
}

void exception_handler(registers_t regs)
{
    panic(exceptions[regs.int_num]);
    //panic(toString(regs.int_num));
}

extern "C" void isr_handler(registers_t regs)
{
    exception_handler(regs);
}

void sendEOI(registers_t regs)
{
    if (regs.int_num >= 40)
        outb(0xA0, 0x20);

    outb(0x20, 0x20);
}

extern "C" void irq_handler(registers_t regs)
{
    sendEOI(regs);

    if (handlers[regs.int_num] != 0)
    {
        isr_t handler = handlers[regs.int_num];
        handler(regs);
    }
}