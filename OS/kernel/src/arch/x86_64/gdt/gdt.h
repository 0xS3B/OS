#pragma once

#include <types.h>

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

typedef struct tssEntry_s {
    uint16_t limitLow;
    uint16_t baseLow;
    uint8_t baseMiddle;
    uint8_t access;
    uint8_t limitHigh:4;
    unsigned flags:4;
    uint8_t baseHigh;
    uint32_t baseUpper;
    uint32_t reserved;
} __attribute__((packed)) tssEntry_t;

typedef struct tss_s {
    uint32_t reserved0;
    uint64_t rsp[3]; // stack pointer
    uint64_t reserved1;
    uint64_t ist[7]; // interrupt stack table
    uint64_t reserved2;
    uint16_t reserved3;
    uint16_t iopbOffset; // the 16-bit offset to the I/O permission bit map
} __attribute__((packed)) tss_t;

#define GDT_LIMIT_LOW(limit)    (limit & 0xFFFF)
#define GDT_LIMIT_HIGH(limit)   ((limit >> 16) & 0xF)

#define GDT_BASE_LOW(base)      (base & 0xFFFF)
#define GDT_BASE_MIDDLE(base)   ((base >> 16) & 0xFF)
#define GDT_BASE_HIGH(base)     ((base >> 24) & 0xFF)
#define GDT_BASE_UPPER(base)    (base >> 32)

typedef struct gdt_s {
    gdtEntry_t gdtEntries[5];
    tssEntry_t tssEntry;
} __attribute__((packed)) gdt_t;


typedef enum {
    GDT_ACCESS_IS_ACCESSED              = (1 << 0),
    GDT_ACCESS_IS_PRESENT               = (1 << 7),
    GDT_ACCESS_READ_WRITE               = (1 << 1), // code: read only    data: read/write
    GDT_ACCESS_IS_EXECUTABLE            = (1 << 3),
    GDT_ACCESS_CODEDATA_SEGMENT         = (1 << 4),
    
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
extern void loadTSS();

void initGDT();