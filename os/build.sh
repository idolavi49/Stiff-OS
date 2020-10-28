nasm -f elf32 kernel.asm -o kasm.o
gcc -m32 -c kernel.c -o kc.o -ffreestanding
gcc -m32 -c include/system.c -o obj/system.o -ffreestanding
gcc -m32 -c include/string.c -o obj/string.o -ffreestanding
gcc -m32 -c include/screen.c -o obj/screen.o -ffreestanding
gcc -m32 -c include/kb.c -o obj/kb.o -ffreestanding
ld -m elf_i386 -T link.ld -o Stiff/boot/kernel.bin kasm.o kc.o obj/system.o obj/string.o obj/screen.o obj/kb.o
qemu-system-i386 -kernel Stiff/boot/kernel.bin
grub-mkrescue -o stiff.iso Stiff/