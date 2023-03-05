#include "idt.h"

#define IDT_SIZE 256

static struct
{
    idt_entry_t entries[IDT_SIZE];
    idt_ptr_t pointer;
} idt;


extern "C" void idt_flush(uint_32);

void idt_set_gate(uint_8 interrupt, uint_32 handler, uint_16 seg_sel, uint_8 flags)
{
    idt.entries[interrupt].offset_lo = low_16(handler);
    idt.entries[interrupt].offset_hi = high_16(handler);
    idt.entries[interrupt].seg_sel = seg_sel;
    idt.entries[interrupt].reserved = 0;
    idt.entries[interrupt].flags = flags;
}

void idt_init()
{
    idt.pointer.limit = sizeof(idt.entries) - 1;
    idt.pointer.base = (uint_32)&idt.entries;
    idt_flush((uint_32)&idt.pointer);
    //memset(idt.entries, 0, sizeof(idt.entries));
    //__asm__ __volatile__("lidtl (%0)" : : "r" (&idt.pointer));
}
