#include "../include/irq.h"
#include "../include/idt.h"
#include "../include/isr.h"
#include "../include/system.h"

#define NUM_IRQS 16

//PIC Constants
//Master
#define PIC1_MASK 0x20  // PIC1 mask register
#define PIC1_BASE 0x20  // The base interrupt number that the PIC should use to send interrupts to the CPU
#define PIC1_ICW1 0x11  // tell the PIC that initialization sequence is starting
#define PIC1_ICW3 0x04  // tell the PIC which IRQ line is connected to the slave PIC
#define PIC1_ICW4 0x01  // tell the PIC to operate in 8086/88 mode
#define PIC1_DATA (PIC1_MASK + 1)

//Slave
#define PIC2_MASK 0xA0  // PIC2 mask register
#define PIC2_BASE 0x28  // The base interrupt number that the PIC should use to send interrupts to the CPU
#define PIC2_ICW1 0x11  // tell the PIC that initialization sequence is starting
#define PIC2_ICW3 0x02  // tell the PIC which IRQ line on the Master PIC is connected to the slave PIC
#define PIC2_ICW4 0x01  // tell the PIC to operate in 8086/88 mode
#define PIC2_DATA (PIC2_MASK + 1)

#define INT_OFFSET 0x08 // interrupt vector offset for the PIC
#define PIC_EOI 0x20    // end of interrupt


static void (*handlers[NUM_IRQS])(struct Registers *) = {NULL};

void irq_install(uint_8 num, void (*handler)(struct Registers *))
{
    handlers[num] = handler;
    IDT_SetGate(32 + num, (void *)handler, 0x08, IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_PRESENT | IDT_FLAG_RING0);
}

void irq_uninstall(uint_8 num)
{
    handlers[num] = NULL;
    IDT_SetGate(32 + num, (void *)0, 0x08, IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_PRESENT | IDT_FLAG_RING0);
}

void irq_init()
{
    for (uint_8 i = 0; i < NUM_IRQS; i++)
    {
        irq_uninstall(i);
    }

    // Master PIC
    outb(PIC1_MASK, PIC1_ICW1);
    outb(PIC1_DATA, PIC1_BASE);
    outb(PIC1_DATA, PIC1_ICW3);
    outb(PIC1_DATA, PIC1_ICW4);

    // Slave PIC
    outb(PIC2_MASK, PIC2_ICW1);
    outb(PIC2_DATA, PIC2_BASE);
    outb(PIC2_DATA, PIC2_ICW3);
    outb(PIC2_DATA, PIC2_ICW4);

    // Set the PICs to use 32-bit interrupt mode
    outb(PIC1_DATA, INT_OFFSET);
    outb(PIC2_DATA, INT_OFFSET);


    IDT_Init();
    asm volatile("sti"); // enable hardware interrupts
}

extern "C" void irq_handler(struct Registers *regs)
{
    // reads the interrupt number from PIC Mask Register
    uint_8 int_num = inb(PIC1_MASK);

    // 32 - 47 reserved  hardware interrupts of PIC
    if (int_num >= 32 && int_num < 48)  
    {
        // 40 - 48 = Slave PIC
        if (int_num >= 40)
        {
            outb(PIC2_MASK, PIC_EOI);
        }
        // 32 - 40 = Master PIC
        outb(PIC1_MASK, PIC_EOI);

        if (handlers[int_num - 32] != NULL)
        {
            void (*handler)(struct Registers *) = handlers[int_num - 32];
            handler(regs);
        }
    }
}