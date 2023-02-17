#include "../include/isr.h"
#include "../include/idt.h"
#include "../include/system.h"

#define NUM_ISRS 48

//extern "C" void isr0(struct Registers *);
//extern "C" void isr1(struct Registers *);
//extern "C" void isr2(struct Registers *);

const char *exceptions[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
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

//initialize array of pointers to function 0 of size NUM_ISRS with argument Registers *
static void (*handlers[NUM_ISRS])(struct Registers *) = {NULL};


void isr_install(uint_8 num, void (*handler)(struct Registers *)) {
    handlers[num] = handler;
    IDT_SetGate(num, (void *)handler, 0x08, IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_PRESENT | IDT_FLAG_RING0);
}

extern "C" void isr_handler(struct Registers *regs)
{
    uint_8 int_num = inb(0x20);         // reads the interrupt number from PIC Mask Register
    if (handlers[int_num] != NULL)
    {
        void (*handler)(struct Registers *) = handlers[int_num];
        handler(regs);
    }
    else if (int_num < NUM_ISRS)
    {
        exception_handler(regs);
    }
}

void exception_handler(struct Registers *regs)
{
    panic(exceptions[regs->int_num]);
}

void isr_init()
{
    for (uint_8 i = 0; i < NUM_ISRS; i++)
    {
        handlers[i] = NULL;
    }

    for (size_t i = 0; i < 32; i++)
    {
        isr_install(i, exception_handler);
    }
}   