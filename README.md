# cloudOS

Learning about operating systems by creating my own operating system.

## Releases

The latest beta release is [cloudOS_0.0.0_beta0.5](http://www.mediafire.com/file/gtxwd7icrc85i4o/cloudOS_0.0.0_beta0.5.iso/file)

Download other bootable releases here: [cloudOS Releases](http://www.mediafire.com/folder/f2c7bklvpphhy/releases)

## Development Details

I am developing this using Ubuntu 18.04 WSL on Windows 10. To install the apt dependencies:

```bash
apt update && apt upgrade
apt install grub2-common grub-pc grub-pc-bin xorriso make g++ binutils libc6-dev-i386
```

QEMU is used for testing purposes and can be downloaded [here](https://www.qemu.org/download/#windows)

The `build.ps1` and `test.ps1` scripts can be executed from the root of the repository for their respective effect.
