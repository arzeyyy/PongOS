#pragma once

#include "util.h"

typedef struct registers
{
    uint_32 gs, fs, es, ds;                         // Pushed data segments
    uint_32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    uint_32 int_num, err_code;                      // Interrupt number and error code
    uint_32 eip, cs, eflags, useresp, ss;           // Pushed by the processor automatically.
} registers_t;

void isr_install();
void isr_init();
extern "C" void isr_handler(registers_t regs);
