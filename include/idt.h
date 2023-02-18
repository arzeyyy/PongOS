#pragma once

// The IDT (interrupt descriptor table) is a data structure that holds information about 
// all the interrupt service routines(ISRs) that the operating system can handle

#include "util.h"



typedef enum{
    IDT_FLAG_GATE_TASK          = 0X5,  // hardware interrupts
    IDT_FLAG_GATE_16BIT_INT     = 0X6,  // 16bit software interrupts
    IDT_FLAG_GATE_16BIT_TRAP    = 0X7,  // 16bit exceptions interrupts
    IDT_FLAG_GATE_32BIT_INT     = 0XE,  // 32bit software interrupts
    IDT_FLAG_GATE_32BIT_TRAP    = 0XF,  // 32bit exceptions interrupts

    IDT_FLAG_RING0              =(0 << 5),
    IDT_FLAG_RING1              =(1 << 5),
    IDT_FLAG_RING2              =(2 << 5),
    IDT_FLAG_RING3              =(3 << 5),

    IDT_FLAG_PRESENT            = 0X80, //enabled/disabled

} IDT_Flags;

void IDT_SetGate(uint_8 interrupt, void *base, uint_16 seg_desc, uint_8 _flags);
void IDT_EnableGate(uint_8 interrupt);
void IDT_DisableGate(uint_8 interrupt);
void idt_Init();
