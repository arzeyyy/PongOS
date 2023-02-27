[org 0x7c00]                        
KERNEL_LOCATION equ 0x1000
                                    

mov [BOOT_DISK], dl                 

                                    
xor ax, ax                          
mov es, ax
mov ds, ax
mov bp, 0x8000
mov sp, bp

mov bx, KERNEL_LOCATION
mov dh, 32              ; number of sectors

mov ah, 0x02            ; reading disk function 
mov al, dh              ; define sectors to read
mov ch, 0x00            ; cylinder 0
mov dh, 0x00            ; head 0
mov cl, 0x02            ; read from 2. sector
mov dl, [BOOT_DISK]
int 0x13                

; vga graphics mode
mov ax, 0x13
int 0x10      

; mov ax, 0xA000
; mov es, ax
; es mov byte [0], 15     

; vga text mode                                 
; mov ah, 0x0
; mov al, 0x3
; int 0x10                




CODE_SEG equ GDT_code - GDT_start
DATA_SEG equ GDT_data - GDT_start

cli
lgdt [GDT_descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax
jmp CODE_SEG:start_protected_mode

jmp $
                                    
BOOT_DISK: db 0

GDT_start:
    GDT_null:
        dd 0x0
        dd 0x0

    GDT_code:
        dw 0xffff               ; limit
        dw 0x0                  ; base (low)
        db 0x0                  ; flags
        db 0b10011010           ; flags + upper limit
        db 0b11001111           ; base (high)
        db 0x0                                   

    GDT_data:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10010010
        db 0b11001111
        db 0x0

GDT_end:

GDT_descriptor:
    dw GDT_end - GDT_start - 1
    dd GDT_start

;VESA_VBE_enable:
;    section .data
;    vesa_info_block dw 0 ; Reserve a 2-byte location for storing the address of the VESA information block
;
;    section .text
;    mov ax, 0x4f00 ; VESA function call, sub-function 0x4f00 = Return VESA information
;    mov es, ax ; Load ES with the high word of the VESA information block address
;    mov bx, 0 ; BX is set to 0 to request the VESA information block
;    int 0x10 ; Call interrupt 0x10 to get the VESA information


[bits 32]
start_protected_mode:
    mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	mov ebp, 0x90000		; 32 bit stack base pointer
	mov esp, ebp

    jmp KERNEL_LOCATION

                                     
 
times 510-($-$$) db 0              
dw 0xaa55