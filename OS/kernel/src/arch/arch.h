#pragma once

#include <arch/include.h>

#if defined(__x86_64__)
    #include ARCH_INCLUDE(interfaces/acpi/acpi.h)
    
    #include ARCH_INCLUDE(memory/gdt/gdt.h)

    #include ARCH_INCLUDE(interrupts/idt/idt.h)
    #include ARCH_INCLUDE(interrupts/ints.h)
    #include ARCH_INCLUDE(interrupts/apic/apic.h)

    #include ARCH_INCLUDE(misc/io.h)

    void arch_init();
#endif