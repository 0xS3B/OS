#pragma once

#include <types.h>

#define GDT_MAX_DESCRIPTORS     3

typedef struct gdtRegister_s {
    uint16_t size;
    uint64_t addr;
} __attribute__((packed)) gdtRegister_t;

typedef struct gdtEntry_s {
    uint16_t limitLow;
    uint16_t baseLow;
    uint8_t baseMiddle;
    uint8_t access;
    uint8_t limitHigh:4;
    unsigned flags:4;
    uint8_t baseHigh;
} __attribute__((packed)) gdtEntry_t;

#define GDT_LIMIT_LOW(limit)    (limit & 0xFFFF)
#define GDT_LIMIT_HIGH(limit)   ((limit >> 16) & 0xF)

#define GDT_BASE_LOW(base)      (base & 0xFFFF)
#define GDT_BASE_MIDDLE(base)   ((base >> 16) & 0xFF)
#define GDT_BASE_HIGH(base)     ((base >> 24) & 0xFF)

typedef struct gdt_s {
    gdtEntry_t gdtEntries[GDT_MAX_DESCRIPTORS];
    // tss
} gdt_t;

typedef enum {
    GDT_ACCESS_IS_PRESENT              = (1 << 7),
    GDT_ACCESS_READ_WRITE              = (1 << 1),
    GDT_ACCESS_IS_EXECUTABLE           = (1 << 3),
    GDT_ACCESS_CODEDATA_SEGMENT        = (1 << 4),
    
    // privilege
    GDT_ACCESS_RING0        = NULL,
    GDT_ACCESS_RING1        = (1 << 5),
    GDT_ACCESS_RING2        = 0x40, // ((1 << 6) - (1 << 5))
    GDT_ACCESS_RING3        = (1 << 6),

} GDT_ACCESSBYTE;

typedef enum {
    // long mode
    GDT_FLAGS_IS_64BITS           = (1 << 1),
    // protected mode
    GDT_FLAGS_IS_32BITS           = (1 << 2),
    GDT_FLAGS_IS_16BITS           = NULL,
    
    GDT_FLAGS_GRANULARITY_1B      = NULL,
    GDT_FLAGS_GRANULARITY_4KIB    = (1 << 3),
} GDT_FLAGS;


extern void loadGDT(gdtRegister_t* gdtReg);

void initGDT();