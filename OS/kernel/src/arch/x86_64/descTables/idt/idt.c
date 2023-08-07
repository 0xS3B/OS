#include "idt.h"

#include <system.h>
#include <arch/x86_64/ints/ints.h>

#include <arch/x86_64/io/io.h>

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
    ioWrite8(0x20, 0x11); /* write ICW1 to PICM, we are gonna write commands to PICM */
    ioWrite8(0xA0, 0x11); /* write ICW1 to PICS, we are gonna write commands to PICS */

    ioWrite8(0x21, 0x20); /* remap PICM to 0x20 (32 decimal) */
    ioWrite8(0xA1, 0x28); /* remap PICS to 0x28 (40 decimal) */

    ioWrite8(0x21, 0x04); /* IRQ2 -> connection to slave */ 
    ioWrite8(0xA1, 0x02);

    ioWrite8(0x21, 0x01); /* write ICW4 to PICM, we are gonna write commands to PICM */
    ioWrite8(0xA1, 0x01); /* write ICW4 to PICS, we are gonna write commands to PICS */

    ioWrite8(0x21, 0x0); /* enable all IRQs on PICM */
    ioWrite8(0xA1, 0x0); /* enable all IRQs on PICS */
    
    for(uint16_t i = 0; i < MAX_INTERRUPTS; i++) {
        idtEntries[i] = setIDTGate(isrs[i], NULL, IDT_ATTR_IS_INT_GATE);
    }

    idtRegister_t idtReg = {
        .size = sizeof(idtEntries) - 1,
        .addr = (uint64_t) &idtEntries,
    };
    loadIDT(&idtReg);

    log(SUCCESS, MODULE_NAME, "Initialized");
}