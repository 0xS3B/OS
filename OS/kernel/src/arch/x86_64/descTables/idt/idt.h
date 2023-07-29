#pragma once

#include <types.h>

#define IDT_MAX_GATES       256

typedef struct idtRegister_s {
    uint16_t size;
    uint64_t addr;
} __attribute__((packed)) idtRegister_t;

typedef struct idtEntry_s {
    uint16_t offsetLow;
    uint16_t segmentSelector; // kernel code segment
    uint8_t istIndex;
    uint8_t attributes; // dpl, present, gate type
    uint16_t offsetMiddle;
    uint32_t offsetHigh;
    uint32_t reserved;
} __attribute__((packed)) idtEntry_t;

typedef enum {
    IDT_ATTR_IS_PRESENT             = (1 << 7),
    IDT_ATTR_IS_INTERRUPT_GATE      = 0b1110,
    IDT_ATTR_IS_TRAP_GATE           = 0b1111,

    // privilege
    IDT_ATTR_RING0        = NULL,
    IDT_ATTR_RING1        = (1 << 5),
    IDT_ATTR_RING2        = 0x40, // ((1 << 6) - (1 << 5))
    IDT_ATTR_RING3        = (1 << 6),
} IDT_ATTRS;


extern void loadIDT(idtRegister_t* idtReg);

void initIDT();