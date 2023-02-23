#include "../include/idt.h"
#include "../include/Graphics/Font.h"

#define IDT_SIZE 256


static struct
{
    idt_entry_t entries[IDT_SIZE];
    idt_ptr_t pointer;
} idt;


extern "C" void idt_flush(uint_32);

void idt_set_gate(uint_8 interrupt, uint_32 base, uint_16 seg_sel, uint_8 flags)
{
    idt.entries[interrupt].base_lo = base & 0xFFFF;
    idt.entries[interrupt].base_hi = (base >> 16) & 0xFFFF;
    idt.entries[interrupt].seg_sel = seg_sel;
    idt.entries[interrupt].reserved = 0;
    idt.entries[interrupt].flags = flags;
}

void idt_init()
{
    idt.pointer.limit = sizeof(idt.entries) - 1;
    idt.pointer.base = (uint_32)&idt.entries;
    memset(idt.entries, 0, sizeof(idt.entries));


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

    idt_flush((uint_32)&idt.pointer);
}