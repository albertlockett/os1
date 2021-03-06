#!/bin/bash
nasm -f elf32 -O0 loader.s
ld -T link.ld -melf_i386 loader.o -o kernel.elf
cp stage2_eltorito iso/boot/grub
cp kernel.elf iso/boot/
cp menu.lst iso/boot/grub


genisoimage -R                              \
                -b boot/grub/stage2_eltorito    \
                -no-emul-boot                   \
                -boot-load-size 4               \
                -A os                           \
                -input-charset utf8             \
                -quiet                          \
                -boot-info-table                \
                -o os.iso                       \
                iso
