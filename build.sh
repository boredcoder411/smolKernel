gcc -m32 -c kernel.c -o kc.o
nasm -f elf32 bootsector.asm -o bootsector.o
nasm -f elf32 bootloader.asm -o bootloader.o
ld -m elf_i386 -T link.ld -o kernel bootloader.o bootsector.o kc.o
rm *.o
qemu-system-i386 -kernel kernel