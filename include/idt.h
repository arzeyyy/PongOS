#pragma once

#include "util.h"

// A struct describing an interrupt gate.
struct idt_entry_struct
{
    uint_16 offset_lo;    // the lower 16 bits of the starting address of the interrupt handler function
    uint_16 seg_sel;    // segment of ISR location
    uint_8 reserved;    // unused field
    uint_8 flags;       // flags specifying the properties of the interrupt handler, type, attribute
    uint_16 offset_hi;    // the upper 16 bits of the starting address of the interrupt handler function
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

void idt_set_gate(uint_8 interrupt, uint_32 handler, uint_16 seg_sel, uint_8 flags);
void idt_init();
