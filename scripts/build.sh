#!/bin/bash
rm -f intermediates/*
make kernel.bin
yes | cp -f intermediates/kernel.bin releases/iso/boot/kernel.bin
if [ -z $1 ]
then
    grub-mkrescue -o releases/cloudOS_latest.iso releases/iso
else
    grub-mkrescue -o releases/cloudOS_$1.iso releases/iso
fi