[bits 32]

gloabl ISR0:
ISR0:
    push 0          ; push interrupt number
    jmp isr_common


isr_common:
