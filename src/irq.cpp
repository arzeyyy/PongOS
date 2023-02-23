#include "../include/irq.h"
#include "../include/idt.h"
#include "../include/isr.h"
#include "../include/system.h"

// not 16 because the Master PIC needs to use one 
// of the interrupt lines (line 2) to signal the Slave PIC
// Master PIC 0 - 7
// Slave PIC 8 - 15
#define NUM_IRQS 15

// PIC Constants
// Master
#define PIC1 0x20
#define PIC1_COMM PIC1          // PIC1 command
#define PIC1_DATA (PIC1 + 1)    // 0x21
#define PIC1_OFFS 0x20          // interrupt number at which the first IRQ of the Master PIC is mapped
#define PIC1_ICW1 0x11          // PIC initialise command
#define PIC1_ICW3 0x04          // tell the PIC which IRQ line is connected to the slave PIC
#define PIC1_ICW4 0x01          // tell the PIC to operate in 8086/88 mode

// Slave
#define PIC2 0xA0
#define PIC2_COMM PIC1          // PIC2 command
#define PIC2_DATA (PIC2 + 1)    // 0xA1
#define PIC2_OFFS 0x28          // nterrupt number at which the first IRQ of the Slave PIC is mapped
#define PIC2_ICW1 0x11          // tell the PIC that initialization sequence is starting
#define PIC2_ICW3 0x02          // tell the PIC which IRQ line on the Master PIC is connected to the slave PIC
#define PIC2_ICW4 0x01          // tell the PIC to operate in 8086/88 mode

#define PIC_EOI 0x20            // end of interrupt



// void irq_install(uint_8 num, void (*handler)(struct Registers *))
// {
//     handlers[num] = handler;
//     //IDT_SetGate(32 + num, (void *)handler, 0x08, IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_PRESENT | IDT_FLAG_RING0);
// }

// void irq_uninstall(uint_8 num)
// {
//     handlers[num] = NULL;
//     //IDT_SetGate(32 + num, (void *)0, 0x08, IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_PRESENT | IDT_FLAG_RING0);
// }

void irq_remap()
{
    // Master PIC
    outb(PIC1_COMM, PIC1_ICW1);
    outb(PIC1_DATA, PIC1_OFFS);
    outb(PIC1_DATA, PIC1_ICW3);
    outb(PIC1_DATA, PIC1_ICW4);
    outb(PIC1_DATA, 0x0);

    // Slave PIC
    outb(PIC2_COMM, PIC2_ICW1);
    outb(PIC2_DATA, PIC2_OFFS);
    outb(PIC2_DATA, PIC2_ICW3);
    outb(PIC2_DATA, PIC2_ICW4);
    outb(PIC2_DATA, 0x0);
}

void irq_init()
{
    irq_remap();
    // for (uint_8 i = 0; i < NUM_IRQS; i++)
    // {
    //     irq_uninstall(i);
    // }

    //remmaping of the irq table


}

