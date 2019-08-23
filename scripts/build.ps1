Remove-Item -Force -Recurse .\intermediates\*
bash -c "make kernel.bin"
Copy-Item -Force .\intermediates\kernel.bin .\releases\iso\boot\kernel.bin
if ($args) {
    bash -c "grub-mkrescue -o releases/cloudOS_$args.iso releases/iso"
}
else {
    bash -c "grub-mkrescue -o releases/cloudOS_latest.iso releases/iso"
}
