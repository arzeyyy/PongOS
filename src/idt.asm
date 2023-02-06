[bits 32]

gloabl i686_IDT_LOAD
i686_IDT_LOAD:
    ; make new call frame
    push ebp        ; save old call frame
    move ebp, esp   ; init new call frame

    ; load idt
    mov eax, [ebp + 8]
    lidt [eax]

    ; restore old call frame
    mov esp, ebp
    pop ebp
    ret


; void __attribute__((cdec1)) i686_IDT_LOAD(IDTDescriptor* IDTDescriptor);