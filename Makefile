GPPPARMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386
INTDIR = intermediates/

objects = $(INTDIR)loader.o $(INTDIR)kernel.o

$(INTDIR)%.o: %.cpp
	g++ $(GPPPARMS) -c -o $@ $<

$(INTDIR)%.o: %.s
	as $(ASPARAMS) -o $@ $<

kernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $(INTDIR)$@ $(objects)

