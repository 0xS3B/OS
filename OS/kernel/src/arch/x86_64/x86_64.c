#include <arch/arch.h>

void arch_init() {
    gdt_init();
    idt_init();
}