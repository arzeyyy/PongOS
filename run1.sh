export PATH=$PATH:/usr/local/i386elfgcc/bin

nasm "src/boot.asm" -f bin -o "build/boot.bin"
nasm "src/kernel_entry.asm" -f elf -o "build/kernel_entry.o"
i386-elf-gcc -ffreestanding -m32 -g -c -fno-common "src/kernel.cpp" -o "build/kernel.o"
i386-elf-gcc -ffreestanding -m32 -g -c -fno-common "include/Graphics/vga.cpp" -o "build/vga.o"
i386-elf-gcc -ffreestanding -m32 -g -c -fno-common "src/util.cpp" -o "build/util.o"
i386-elf-gcc -ffreestanding -m32 -g -c -fno-common "src/Text.cpp" -o "build/Text.o"
i386-elf-gcc -ffreestanding -m32 -g -c -fno-common "src/Font.cpp" -o "build/Font.o"
i386-elf-gcc -ffreestanding -m32 -g -c -fno-common "src/system.cpp" -o "build/system.o"

i386-elf-gcc -ffreestanding -m32 -g -c -fno-common "src/idt.cpp" -o "build/idt.o"
nasm "src/idt.asm" -f elf -o "build/idt_asm.o"
i386-elf-gcc -ffreestanding -m32 -g -c -fno-common "src/isr.cpp" -o "build/isr.o"
nasm "src/isr.asm" -f elf -o "build/isr_asm.o"
i386-elf-gcc -ffreestanding -m32 -g -c -fno-common "src/irq.cpp" -o "build/irq.o"

nasm "src/zeroes.asm" -f bin -o "build/zeroes.bin"
 
i386-elf-ld -o "build/full_kernel.bin" -Ttext 0x1000 "build/kernel_entry.o" "build/kernel.o" "build/util.o" "build/Text.o" "build/vga.o" "build/Font.o" "build/system.o" "build/idt.o" "build/isr.o" "build/irq.o" "build/idt_asm.o" "build/isr_asm.o" --oformat binary 


cat "build/boot.bin" "build/full_kernel.bin" "build/zeroes.bin"  > "build/OS.bin"

qemu-system-x86_64  -drive format=raw,file="build/OS.bin",index=0,if=floppy,  -m 128M
