#include "idt.h"

#include <system.h>

#include <arch/include.h>
#include ARCH_INCLUDE(interrupts/ints.h)
#include ARCH_INCLUDE(misc/asm.h)

#define MODULE_NAME "IDT"

static __attribute__((aligned(8))) idt_entry_t idtEntries[MAX_INTERRUPTS];

static idt_entry_t idt_setGate(uint64_t offset, uint8_t istIndex, uint8_t attributes) {
    idt_entry_t gate;

    gate.offsetLow = IDT_OFFSET_LOW(offset);
    gate.segmentSelector = 0x8; // GDT offset code segment
    gate.istIndex = istIndex;
    gate.attributes = IDT_ATTR_IS_PRESENT | IDT_ATTR_RING0 | attributes;
    gate.offsetMiddle = IDT_OFFSET_MIDDLE(offset);
    gate.offsetHigh = IDT_OFFSET_HIGH(offset);
    gate.reserved = 0;

    return gate;
}

void idt_init() {    
    for(uint16_t i = 0; i < MAX_INTERRUPTS; i++) {
        idtEntries[i] = idt_setGate(isrs[i], NULL, IDT_ATTR_IS_INT_GATE);
    }

    idt_register_t idtReg = {
        .size = sizeof(idtEntries) - 1,
        .addr = (uint64_t) &idtEntries,
    };
    idt_load(&idtReg);

    ASM_SET_INT

    log(LOG_SUCCESS, MODULE_NAME, "Initialized");
}