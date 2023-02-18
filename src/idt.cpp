#include "../include/idt.h"


#define IDT_SIZE 256

typedef struct {
    uint_16 base_low;       // the lower 16 bits of the starting address of the interrupt handler function
    uint_16 seg_selector;   // segment of ISR location
    uint_8 reserved;        // unused field
    uint_8 flags;           // flags specifying the properties of the interrupt handler, type, attribute
    uint_16 base_high;      // the upper 16 bits of the starting address of the interrupt handler function

} __attribute__((packed)) IDT_Entry;

typedef struct{
    uint_16 limit;          // the size of the IDT in bytes
    IDT_Entry* base;
} __attribute__((packed)) IDT_Pointer;


static struct
{
    IDT_Entry entries[IDT_SIZE];
    IDT_Pointer pointer;
} idt;

// IDT_Entry IDT[IDT_SIZE];
// IDT_Pointer IDT_Ptr = { sizeof(IDT) - 1, IDT };

extern "C" void IDT_LOAD(IDT_Pointer *IDT_Ptr);

void IDT_SetGate(uint_8 interrupt, void *base, uint_16 seg_selector, uint_8 flags)
{
    idt.entries[interrupt].base_low = (uint_32)base & 0xFFFF;
    idt.entries[interrupt].base_high = ((uint_32)base >> 16) & 0xFFFF;
    idt.entries[interrupt].seg_selector = seg_selector;
    idt.entries[interrupt].reserved = 0;
    idt.entries[interrupt].flags = flags;
}

void IDT_EnableGate(uint_8 interrupt)
{
    FLAG_SET(idt.entries[interrupt].flags, IDT_FLAG_PRESENT);
}

void IDT_DisableGate(uint_8 interrupt)
{
    FLAG_UNSET(idt.entries[interrupt].flags, IDT_FLAG_PRESENT);
}

void IDT_Init()
{
    idt.pointer.limit = sizeof(idt.entries) - 1;
    idt.pointer.base = idt.entries;
    memset(idt.entries, 0, sizeof(idt.entries));
    IDT_LOAD(&idt.pointer);
}