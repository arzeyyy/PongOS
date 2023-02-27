ENTRY(_start)


/* INPUT
{
    build/kernel_entry.o
    build/kernel.o
    build/util.o
    build/Text.o
    build/vga.o
    build/Font.o
    build/system.o
    build/idt.o 
    build/isr.o
    build/irq.o
    build/idt_asm.o
    build/isr_asm.o
    build/timer.o
    build/irq_asm.o
    build/keyboard.o
    build/monitor.o
}

OUTPUT
{
    build/full_kernel.bin
} */

SECTIONS
{
    . = 0x1000;

    .text : ALIGN(0x1000)
    {
        *(.text)
    }

    .data : ALIGN(0x1000)
    {
        *(.data)
    }

    .rodata : ALIGN(0x1000)
    {
        *(.rodata)
    }

    .bss : ALIGN(0x1000)
    {
        *(COMMON)
        *(.bss)
    }
}