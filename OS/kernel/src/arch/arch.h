#pragma once

#if defined(__x86_64__)
    #include <arch/x86_64/descTables/gdt/gdt.h>
    #include <arch/x86_64/descTables/idt/idt.h>
    #include <arch/x86_64/io/io.h>

    void initArch();
#endif