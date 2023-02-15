[bits 32]

section .text

gloabl int_bottom:
int_bottom:

    pushad          ; Save the general-purpose registers
    push ds         ; Save the data segment selector
    push es         ; Save the extra segment selector
    push fs
    push gs

    push %esp       ; stack pointer
    push (int_num)
    call isr_handler

    movl %eax, %esp 

    pop gs
    pop fs
    pop es          ; Restore the extra segment selector
    pop ds          ; Restore the data segment selector
    popad           ; Restore the general-purpose registers
    
    iretd           ; Return from the interrupt



    ; mov ax, CODE_SEG ; Load the code segment selector
    ; mov ds, ax
    ; mov es, ax

    ; Read the scancode from the keyboard controller
    ; Place it in a buffer or process it as necessary


.data
    int_num: .byte 0

isr_common:
; [extern isr1_handler]
; isr1:

;     pusha
;     call isr1_handler
;     popa

;     iretd
;     gloabl isr1: