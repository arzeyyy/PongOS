[bits 32]

section .text

gloabl isr_common:

; Define macro for generating ISR functions
%macro ISR 1
    global isr%1
    isr%1:
        pushad          ; Save the general-purpose registers
        push ds         ; Save the data segment selector
        push es         ; Save the extra data segment selector
        push fs         ; save the thread-local storage segment selector
        push gs         ; save the process-specific segment selector

        push dword %1   ; Push interrupt number onto stack

        ;push %esp       ; stack pointer

        push (int_num)
        call isr_handler

        mov esp, ebp    ; Move stack pointer back to base pointer

        pop gs
        pop fs
        pop es       
        pop ds          
        popad           ; Restore the general-purpose registers

        add esp, 4      ; Remove interrupt number from stack

        iretd           ; Return from the interrupt
%endmacro

section .data
    int_num: db 0 
    ;int_num: .byte 0

section .bss
    ; Define buffer for interrupt stack
    stack:
        resb 4096
        
; [extern isr1_handler]
; isr1:

;     pusha
;     call isr1_handler
;     popa

;     iretd
;     gloabl isr1: