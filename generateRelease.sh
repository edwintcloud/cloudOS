#!/bin/bash
yes | cp -f target/x86_64-cloud_os/debug/bootimage-cloud_os.bin releases/iso/boot/kernel.bin
if [ -z $1 ]
then
    grub-mkrescue -o releases/cloudOS_latest.iso releases/iso
else
    grub-mkrescue -o releases/cloudOS_$1.iso releases/iso
fi