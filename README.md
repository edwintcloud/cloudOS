# cloudOS

Learning about operating systems by creating my own operating system.

Download bootable releases here: [cloudOS Releases](http://www.mediafire.com/folder/f2c7bklvpphhy/releases)

## Development Details

I am developing this using Ubuntu 18.04 WSL on Windows 10. To install the apt dependencies:

```bash
apt update && apt upgrade
apt install grub2-common grub-pc grub-pc-bin xorriso qemu-system-i386 make g++ binutils libc6-dev-i386
```

Xmimg X Server is used for testing purposes and can be downloaded [here](https://sourceforge.net/projects/xming/).

The `build.sh` and `test.sh` scripts can be executed from the root of the repository for their respective effect.
