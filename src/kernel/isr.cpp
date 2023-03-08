#include "isr.h"

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
};

isr_t handlers[256]; // array of function pointers

void isr_init()
{
    // Install the ISRs
    idt_set_gate(0, (uint_32)isr0, 0x08, 0x8E);
    idt_set_gate(1, (uint_32)isr1, 0x08, 0x8E);
    idt_set_gate(2, (uint_32)isr2, 0x08, 0x8E);
    idt_set_gate(3, (uint_32)isr3, 0x08, 0x8E);
    idt_set_gate(4, (uint_32)isr4, 0x08, 0x8E);
    idt_set_gate(5, (uint_32)isr5, 0x08, 0x8E);
    idt_set_gate(6, (uint_32)isr6, 0x08, 0x8E);
    idt_set_gate(7, (uint_32)isr7, 0x08, 0x8E);
    idt_set_gate(8, (uint_32)isr8, 0x08, 0x8E);
    idt_set_gate(9, (uint_32)isr9, 0x08, 0x8E);
    idt_set_gate(10, (uint_32)isr10, 0x08, 0x8E);
    idt_set_gate(11, (uint_32)isr11, 0x08, 0x8E);
    idt_set_gate(12, (uint_32)isr12, 0x08, 0x8E);
    idt_set_gate(13, (uint_32)isr13, 0x08, 0x8E);
    idt_set_gate(14, (uint_32)isr14, 0x08, 0x8E);
    idt_set_gate(15, (uint_32)isr15, 0x08, 0x8E);
    idt_set_gate(16, (uint_32)isr16, 0x08, 0x8E);
    idt_set_gate(17, (uint_32)isr17, 0x08, 0x8E);
    idt_set_gate(18, (uint_32)isr18, 0x08, 0x8E);
    idt_set_gate(19, (uint_32)isr19, 0x08, 0x8E);
    idt_set_gate(20, (uint_32)isr20, 0x08, 0x8E);
    idt_set_gate(21, (uint_32)isr21, 0x08, 0x8E);
    idt_set_gate(22, (uint_32)isr22, 0x08, 0x8E);
    idt_set_gate(23, (uint_32)isr23, 0x08, 0x8E);
    idt_set_gate(24, (uint_32)isr24, 0x08, 0x8E);
    idt_set_gate(25, (uint_32)isr25, 0x08, 0x8E);
    idt_set_gate(26, (uint_32)isr26, 0x08, 0x8E);
    idt_set_gate(27, (uint_32)isr27, 0x08, 0x8E);
    idt_set_gate(28, (uint_32)isr28, 0x08, 0x8E);
    idt_set_gate(29, (uint_32)isr29, 0x08, 0x8E);
    idt_set_gate(30, (uint_32)isr30, 0x08, 0x8E);
    idt_set_gate(31, (uint_32)isr31, 0x08, 0x8E);

    // Remap the PIC
    pic_remap();

    // Install the IRQs
    idt_set_gate(32, (uint_32)irq0, 0x08, 0x8E);
    idt_set_gate(33, (uint_32)irq1, 0x08, 0x8E);
    idt_set_gate(34, (uint_32)irq2, 0x08, 0x8E);
    idt_set_gate(35, (uint_32)irq3, 0x08, 0x8E);
    idt_set_gate(36, (uint_32)irq4, 0x08, 0x8E);
    idt_set_gate(37, (uint_32)irq5, 0x08, 0x8E);
    idt_set_gate(38, (uint_32)irq6, 0x08, 0x8E);
    idt_set_gate(39, (uint_32)irq7, 0x08, 0x8E);
    idt_set_gate(40, (uint_32)irq8, 0x08, 0x8E);
    idt_set_gate(41, (uint_32)irq9, 0x08, 0x8E);
    idt_set_gate(42, (uint_32)irq10, 0x08, 0x8E);
    idt_set_gate(43, (uint_32)irq11, 0x08, 0x8E);
    idt_set_gate(44, (uint_32)irq12, 0x08, 0x8E);
    idt_set_gate(45, (uint_32)irq13, 0x08, 0x8E);
    idt_set_gate(46, (uint_32)irq14, 0x08, 0x8E);
    idt_set_gate(47, (uint_32)irq15, 0x08, 0x8E);

    //_idt_flush();
    idt_init();
}

void isr_install(uint_8 n, isr_t handler)
{
    handlers[n] = handler;
}

void exception_handler(registers_t regs)
{
    panic(exceptions[regs.int_num]);
    // panic(toString(regs.int_num));
}

extern "C" void isr_handler(registers_t regs)
{
    exception_handler(regs);
}

void sendEOI(registers_t regs)
{
    if (regs.int_num >= 40)
        outb(PIC2, PIC_EOI);

    outb(PIC1, PIC_EOI);
}

extern "C" void irq_handler(registers_t regs)
{
    // monitor_write("IRQ!!!");
    sendEOI(regs);

    if (handlers[regs.int_num] != NULL)
    {
        // assign handlers to handler variable
        isr_t handler = handlers[regs.int_num];
        handler(regs);
    }
}