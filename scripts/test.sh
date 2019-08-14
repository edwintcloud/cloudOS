#!/bin/bash
export DISPLAY=:0
if [ -z $1 ]
then
    qemu-system-x86_64 -cdrom releases/cloudOS_latest.iso
else
    qemu-system-x86_64 -cdrom releases/cloudOS_$1.iso
fi