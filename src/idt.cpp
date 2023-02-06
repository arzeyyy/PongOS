#include "../include/idt.h"

typedef struct {
    uint_16 base_low;
    uint_16 selctor;    // a code segment selector
    uint_8 reserved;
    uint_8 flags;
    uint_16 base_high;

} __attribute__((packed)) IDTEntry;

typedef struct{
    uint_16 limit;
    IDTEntry* ptr;
} __attribute__((packed)) IDTDescriptor;


IDTEntry g_IDT[256];
IDTDescriptor g_IDTDescriptor = { sizeof(g_IDT) - 1, g_IDT };

void __attribute__((cdec1)) i686_IDT_LOAD(IDTDescriptor* IDTDescriptor);

void i686_IDT_SetGate(int interrupt, void* base, uint_16 seg_desc, uint_16 _flags)
{
    g_IDT[interrupt].base_low = ((uint_32)base) & 0xFFFF;
    g_IDT[interrupt].selctor = seg_desc;
    g_IDT[interrupt].reserved = 0;
    g_IDT[interrupt].flags = _flags;
    g_IDT[interrupt].base_high = ((uint_32)base >> 16) & 0xFFFF;
}

void i686_IDT_EnableGate(int interrupt)
{
    FLAG_SET(g_IDT[interrupt].flags, IDT_FLAG_PRESENT);
}

void i686_IDT_EnableGate(int interrupt)
{
    FLAG_UNSET(g_IDT[interrupt].flags, IDT_FLAG_PRESENT);
}

void i686_IDT_Init()
{
    i686_IDT_LOAD(&g_IDTDescriptor);
}