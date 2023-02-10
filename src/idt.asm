[bits 32]

gloabl IDT_LOAD
IDT_LOAD:
    ; make new call frame
    push ebp            ; save old call frame on the stack
    move ebp, esp       ; init new call frame with stack ptr

    ; load idt
    mov eax, [ebp + 8]  ; retrive pointer to IDT_Descriptor from stack
    lidt [eax]          ; load IDT from IDT_Descriptor

    ; restore old call frame 
    mov esp, ebp        ; restores the stack pointer
    pop ebp             ; restores the original call frame
    ret                 ; return control to caller


; void __attribute__((cdec1)) IDT_LOAD(IDTDescriptor* IDTDescriptor);