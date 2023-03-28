# set path to i386-elf-gcc bin directory
export PATH=$PATH:/usr/local/i386elfgcc/bin

# compile C++ code into object files
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/main.cpp" -o "build/kernel.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/drivers/vga.cpp" -o "build/vga.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/drivers/keyboard.cpp" -o "build/keyboard.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/util.cpp" -o "build/util.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/Font.cpp" -o "build/Font.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/pong/Game.cpp" -o "build/Game.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/pong/menu.cpp" -o "build/menu.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/drivers/timer.cpp" -o "build/timer.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/system.cpp" -o "build/system.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/idt.cpp" -o "build/idt.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/isr.cpp" -o "build/isr.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/kernel/gfx.cpp" -o "build/gfx.o"
i386-elf-gcc -ffreestanding -g -c -fno-common "src/drivers/pic.cpp" -o "build/pic.o"


# compile assembly code into object files
nasm "src/kernel/boot.asm" -f bin -o "build/boot.bin"
nasm "src/kernel/zeroes.asm" -f bin -o "build/zeroes.bin"
nasm "src/kernel/kernel_entry.asm" -f elf -o "build/kernel_entry.o"
nasm "src/kernel/idt.asm" -f elf -o "build/idt_asm.o"
nasm "src/kernel/isr.asm" -f elf -o "build/isr_asm.o"
nasm "src/kernel/irq.asm" -f elf -o "build/irq_asm.o"


# link all object files into a binary file
i386-elf-ld -o  "build/full_kernel.bin" -T link.ld  "build/kernel_entry.o" "build/Game.o" "build/kernel.o" "build/vga.o" "build/gfx.o" "build/util.o" "build/menu.o" "build/keyboard.o" "build/Font.o" "build/system.o" "build/idt.o" "build/isr.o" "build/pic.o" "build/idt_asm.o" "build/isr_asm.o" "build/timer.o" "build/irq_asm.o" -g -L/usr/local/i386elfgcc/lib/gcc/i386-elf/12.2.0 -lgcc  --oformat binary 


cat "build/boot.bin" "build/full_kernel.bin" "build/zeroes.bin"  > "build/OS.bin"

qemu-system-x86_64 -drive format=raw,file="build/OS.bin",index=0,if=floppy,  -m 128M

i386-elf-objcopy -I binary -O elf32-i386 "build/OS.bin" "build/OS.elf"

chmod +x "build/OS.elf"