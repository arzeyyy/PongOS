[bits 32]

gloabl i686_ISR0:
i686_ISR0:
    push 0          ; push interrupt number
    jmp isr_common


isr_common:
