include ../Makefile.cfg

SRCS := $(call rwildcard, $(SRCDIR), *.c)
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(OBJS) link

$(OBJS): $(SRCS)
	mkdir -m 777 -p $(OBJDIR)
	$(CC) $(CFLAGS) -Isrc/include -c $< -o $@

link: $(OBJS)	
	$(LD) $(LDFLAGS) -Tkernel.ld $< -o ../bin/kernel.elf