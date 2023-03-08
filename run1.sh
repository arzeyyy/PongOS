export PATH=$PATH:/usr/local/i386elfgcc/bin

nasm "src/kernel/boot.asm" -f bin -o "build/boot.bin"
nasm "src/kernel/kernel_entry.asm" -f elf -o "build/kernel_entry.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/main.cpp" -o "build/kernel.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/drivers/screen.cpp" -o "build/screen.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/drivers/keyboard.cpp" -o "build/keyboard.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/util.cpp" -o "build/util.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/Font.cpp" -o "build/Font.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/drivers/timer.cpp" -o "build/timer.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/system.cpp" -o "build/system.o"

i386-elf-gcc -ffreestanding -march=i686 -g -c -fno-common "src/kernel/idt.cpp" -o "build/idt.o"
nasm "src/kernel/idt.asm" -f elf -o "build/idt_asm.o"
i386-elf-gcc -ffreestanding -march=i686 -g -c -fno-common "src/kernel/isr.cpp" -o "build/isr.o"
nasm "src/kernel/isr.asm" -f elf -o "build/isr_asm.o"
i386-elf-gcc -ffreestanding -march=i686 -g -c -fno-common "src/drivers/pic.cpp" -o "build/pic.o"
nasm "src/kernel/irq.asm" -f elf -o "build/irq_asm.o"

nasm "src/kernel/zeroes.asm" -f bin -o "build/zeroes.bin"
 
i386-elf-ld -o  "build/full_kernel.bin" -T link.ld  "build/kernel_entry.o" "build/kernel.o" "build/screen.o" "build/util.o" "build/keyboard.o" "build/Font.o" "build/system.o" "build/idt.o" "build/isr.o" "build/pic.o" "build/idt_asm.o" "build/isr_asm.o" "build/timer.o" "build/irq_asm.o" -g --oformat binary 


cat "build/boot.bin" "build/full_kernel.bin" "build/zeroes.bin"  > "build/OS.bin"

qemu-system-x86_64 -drive format=raw,file="build/OS.bin",index=0,if=floppy,  -m 128M

i386-elf-objcopy -I binary -O elf32-i386 "build/OS.bin" "build/OS.elf"

chmod +x "build/OS.elf"