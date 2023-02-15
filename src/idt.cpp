#include "../include/idt.h"


#define IDT_SIZE 256

typedef struct {
    uint_16 base_low;       // the lower 16 bits of the starting address of the interrupt handler function
    uint_16 seg_selctor;    // segment of ISR location
    uint_8 reserved;        // unused field
    uint_8 flags;           // flags specifying the properties of the interrupt handler, type, attribute
    uint_16 base_high;      // the upper 16 bits of the starting address of the interrupt handler function

} __attribute__((packed)) IDT_Entry;

typedef struct{
    uint_16 limit;          // the size of the IDT in bytes
    IDT_Entry* ptr;
} __attribute__((packed)) IDT_Pointer;


static struct
{
    IDT_Entry entries[IDT_SIZE];    //256 interrupt vectors
    IDT_Pointer pointer = {sizeof(entries) - 1, entries};
} idt;

// IDT_Entry IDT[IDT_SIZE];
// IDT_Pointer IDT_Ptr = { sizeof(IDT) - 1, IDT };

void __attribute__((cdec1)) IDT_LOAD(IDT_Pointer* IDT_Ptr);

void IDT_SetGate(uint_8 interrupt, void* base, uint_16 seg_desc, uint_16 _flags)
{
    idt.entries[interrupt].base_low = ((uint_32)base) & 0xFFFF;
    idt.entries[interrupt].seg_selctor = seg_desc;
    idt.entries[interrupt].reserved = 0;
    idt.entries[interrupt].flags = _flags;
    idt.entries[interrupt].base_high = ((uint_32)base >> 16) & 0xFFFF;

    outb(0x21, 0xfd);
    outb(0xa1, 0xff);
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
    memset(idt.entries, 0, IDT_SIZE);
    IDT_LOAD(&idt.pointer);
}