GPPPARMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386
INTDIR = intermediates/
RELDIR = releases/

objects = $(INTDIR)loader.o $(INTDIR)gdt.o $(INTDIR)port.o $(INTDIR)interruptstubs.o $(INTDIR)interrupts.o $(INTDIR)keyboard.o $(INTDIR)kernel.o

$(INTDIR)%.o: %.cpp
	g++ $(GPPPARMS) -c -o $@ $<

$(INTDIR)%.o: %.s
	as $(ASPARAMS) -o $@ $<

kernel.iso: kernel.bin
	yes | cp -f $(INTDIR)kernel.bin $(RELDIR)iso/boot/kernel.bin
	grub-mkrescue -o $(RELDIR)cloudOS_latest.iso $(RELDIR)iso
	
kernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $(INTDIR)$@ $(objects)


.PHONY: clean
clean:
	rm -f $(objects) $(INTDIR)kernel.bin  $(RELDIR)*.iso $(RELDIR)iso/boot/kernel.bin