GPPPARMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings
ASPARAMS = --32
LDPARAMS = -melf_i386
INTDIR = intermediates/
RELDIR = releases/

objects = $(INTDIR)loader.o \
		  $(INTDIR)gdt.o \
		  $(INTDIR)driver.o \
		  $(INTDIR)port.o \
		  $(INTDIR)interruptstubs.o \
		  $(INTDIR)interrupts.o \
		  $(INTDIR)keyboard.o \
		  $(INTDIR)mouse.o \
		  $(INTDIR)kernel.o

run: kernel.iso
	(killall VirtualBox && sleep 1) || true
	VirtualBox --startvm 'CloudOS' &

$(INTDIR)%.o: %.cpp
	mkdir -p $(@D)
	g++ $(GPPPARMS) -c -o $@ $<

$(INTDIR)%.o: %.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<

kernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $(INTDIR)$@ $(objects)

kernel.iso: kernel.bin
	yes | cp -f $(INTDIR)kernel.bin $(RELDIR)iso/boot/kernel.bin
	grub-mkrescue -o $(RELDIR)cloudOS_latest.iso $(RELDIR)iso

.PHONY: clean
clean:
	rm -f $(objects) $(INTDIR)kernel.bin  $(RELDIR)*.iso $(RELDIR)iso/boot/kernel.bin