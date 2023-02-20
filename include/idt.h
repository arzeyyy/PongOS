#pragma once

#include "util.h"

// A struct describing an interrupt gate.
struct idt_entry_struct
{
    uint_16 base_lo;    // the lower 16 bits of the starting address of the interrupt handler function
    uint_16 seg_sel;    // segment of ISR location
    uint_8 reserved;    // unused field
    uint_8 flags;       // flags specifying the properties of the interrupt handler, type, attribute
    uint_16 base_hi;    // the upper 16 bits of the starting address of the interrupt handler function
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct idt_ptr_struct
{
    uint_16 limit;
    uint_32 base; // The address of the first element in our idt_entry_t array.
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

void idt_set_gate(uint_8 interrupt, uint_32 base, uint_16 seg_sel, uint_8 flags);
void idt_init();

// These extern directives let us access the addresses of our ASM ISR handlers.
extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();
extern "C" void isr32();
extern "C" void isr33();
extern "C" void isr34();
extern "C" void isr35();
extern "C" void isr36();
extern "C" void isr37();
extern "C" void isr38();
extern "C" void isr39();
extern "C" void isr40();
extern "C" void isr41();
extern "C" void isr42();
extern "C" void isr43();
extern "C" void isr44();
extern "C" void isr45();
extern "C" void isr46();
extern "C" void isr47();