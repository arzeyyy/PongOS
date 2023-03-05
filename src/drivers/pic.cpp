#include "pic.h"

// not 16 because the Master PIC needs to use one 
// of the interrupt lines (line 2) to signal the Slave PIC
// Master PIC 0 - 7
// Slave PIC 8 - 15
#define NUM_IRQS 15

// Master
#define PIC1_DATA (PIC1 + 1)    // 0x21, data register of the Master PIC
#define PIC1_OFFS 0x20          // interrupt number at which the first IRQ of the Master PIC is mapped
#define PIC1_ICW1 0x11          // PIC initialize command
#define PIC1_ICW3 0x04          // tells the PIC which IRQ line is connected to the slave PIC
#define PIC1_ICW4 0x01          // tells the PIC to operate in 8086/88 mode

// Slave
#define PIC2_DATA (PIC2 + 1)    // 0xA1, data register of the Slave PIC
#define PIC2_OFFS 0x28          // interrupt number at which the first IRQ of the Slave PIC is mapped
#define PIC2_ICW1 0x11          // tells the PIC that initialization sequence is starting
#define PIC2_ICW3 0x02          // tells the PIC which IRQ line on the Master PIC is connected to the slave PIC
#define PIC2_ICW4 0x01          // tells the PIC to operate in 8086/88 mode


void pic_remap()
{
    // Master PIC
    outb(PIC1, PIC1_ICW1);
    outb(PIC1_DATA, PIC1_OFFS);
    outb(PIC1_DATA, PIC1_ICW3);
    outb(PIC1_DATA, PIC1_ICW4);
    outb(PIC1_DATA, 0x0);

    // Slave PIC
    outb(PIC2, PIC2_ICW1);
    outb(PIC2_DATA, PIC2_OFFS);
    outb(PIC2_DATA, PIC2_ICW3);
    outb(PIC2_DATA, PIC2_ICW4);
    outb(PIC2_DATA, 0x0);
}


