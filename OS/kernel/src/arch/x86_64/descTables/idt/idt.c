#include "idt.h"

#include <arch/x86_64/ints/ints.h>

#include <log/log.h>
#define MODULE_NAME "IDT"

static __attribute__((aligned(8))) idtEntry_t idtEntries[MAX_INTERRUPTS];

static idtEntry_t setIDTGate(uint64_t offset, uint8_t istIndex, uint8_t attributes) {
    idtEntry_t gate;

    gate.offsetLow = IDT_OFFSET_LOW(offset);
    gate.segmentSelector = 0x8; // code segment
    gate.istIndex = istIndex;
    gate.attributes = IDT_ATTR_IS_PRESENT | IDT_ATTR_RING0 | attributes;
    gate.offsetMiddle = IDT_OFFSET_MIDDLE(offset);
    gate.offsetHigh = IDT_OFFSET_HIGH(offset);
    gate.reserved = 0;

    return gate;
}

void initIDT() {
    for(uint16_t i = 0; i < MAX_INTERRUPTS; i++) {
        idtEntries[i] = setIDTGate(interruptVectors[i], NULL, IDT_ATTR_IS_INT_GATE);
    }

    idtRegister_t idtReg = {
        .size = sizeof(idtEntries) - 1,
        .addr = (uint64_t) &idtEntries,
    };
    loadIDT(&idtReg);

    log(SUCCESS, MODULE_NAME, "Initialized");

    // test
    asm("int $0");
}