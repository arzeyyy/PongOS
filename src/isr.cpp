#include "../include/isr.h"
#include "../include/idt.h"
#include "../include/system.h"

#define NUM_ISRS 48

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

// initialize array of pointers to function 0 of size NUM_ISRS with argument Registers *
static void (*handlers[NUM_ISRS])(registers_t) = {NULL};

void isr_install(uint_8 num, void (*handler)(registers_t))
{
    handlers[num] = handler;
    //IDT_SetGate(num, (void *)handler, 0x08, IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_PRESENT | IDT_FLAG_RING0);
}

void exception_handler(registers_t regs)
{
    //panic(exceptions[regs.int_num]);
    //panic(toString(regs.int_num));
}

extern "C" void isr_handler(registers_t regs)
{
    // if (regs.int_num < 32)
    // {
    //     outb(0x20, 0x20); // send reset signal to master PIC
    //     if (regs.int_num >= 16)
    //     {
    //         outb(0xA0, 0x20); // send reset signal to slave PIC
    //     }
    // }

    // if (regs.int_num < sizeof(exceptions) / sizeof(char *))
    // {
    // }
   // panic(toString(regs.int_num));
    panic(exceptions[regs.int_num]);

    //uint_8 int_num = inb(0x21); // reads the interrupt number from PIC Interrupt Request Register
    //if (handlers[int_num] != NULL)
    //{
    //    void (*handler)(registers_t) = handlers[int_num];
    //    handler(regs);
    //}
    //else if (int_num < NUM_ISRS)
    //{
    //   exception_handler(regs);
    //}
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