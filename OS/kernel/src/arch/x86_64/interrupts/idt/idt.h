#pragma once

#include <types.h>

typedef struct {
    uint16_t size;
    uint64_t addr;
} __attribute__((packed)) idt_register_t;

typedef struct {
    uint16_t offsetLow;
    uint16_t segmentSelector; // kernel code segment
    uint8_t istIndex;
    uint8_t attributes; // dpl, present, gate type
    uint16_t offsetMiddle;
    uint32_t offsetHigh;
    uint32_t reserved;
} __attribute__((packed)) idt_entry_t;

#define IDT_OFFSET_LOW(offset)      (offset & 0xFFFF)
#define IDT_OFFSET_MIDDLE(offset)   ((offset >> 16) & 0xFFFF)
#define IDT_OFFSET_HIGH(offset)     (offset >> 32)

typedef enum {
    IDT_ATTR_IS_PRESENT             = (1 << 7),
    IDT_ATTR_IS_INT_GATE            = 0b1110,
    IDT_ATTR_IS_TRAP_GATE           = 0b1111,

    // privilege
    IDT_ATTR_RING0        = NULL,
    IDT_ATTR_RING1        = (1 << 5),
    IDT_ATTR_RING2        = 0x40, // ((1 << 6) - (1 << 5))
    IDT_ATTR_RING3        = (1 << 6),
} IDT_ATTRS;


extern void idt_load(idt_register_t* idtReg);

void idt_init();