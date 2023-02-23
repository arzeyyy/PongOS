#pragma once

#include "util.h"

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

typedef struct registers
{
    uint_32 ds;                                     // Data segment selector
    uint_32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    uint_32 int_num, err_code;                      // Interrupt number and error code 
    uint_32 eip, cs, eflags, useresp, ss;           // Pushed by the processor automatically.
} registers_t;

typedef void (*isr_t)(registers_t);
void register_interrupt_handler(uint_8 n, isr_t handler);

void isr_init();
extern "C" void isr_handler(registers_t regs);
