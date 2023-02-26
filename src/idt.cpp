#include "../include/idt.h"
#include "../include/isr.h"
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
}

void _idt_flush()
{
    idt_flush((uint_32)&idt.pointer);
}