if ($args) {
    qemu-system-i386 -cdrom .\releases\cloudOS_$args.iso
}
else {
    qemu-system-i386 -cdrom  .\releases\cloudOS_latest.iso
}