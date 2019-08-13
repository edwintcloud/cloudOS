#!/bin/bash
rm intermediates/*
make kernel.bin
yes | cp -f intermediates/kernel.bin releases/iso/boot/kernel.bin
grub-mkrescue -o releases/cloudOS-$1.iso releases/iso