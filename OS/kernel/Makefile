include ../Makefile.cfg

all: $(OBJS) link

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ mkdir -m 777 -p $(@D)
	$(CC) $(CFLAGS) -Isrc/include -c $^ -o $@

$(OBJDIR)/%_asm.o: $(SRCDIR)/%.asm
	@ mkdir -m 777 -p $(@D)
	$(AS) $(ASMFLAGS) -Isrc/include $^ -o $@

link: $(OBJS)	
	$(LD) $(LDFLAGS) -Tkernel.ld $^ -o $(BINDIR)/kernel.elf