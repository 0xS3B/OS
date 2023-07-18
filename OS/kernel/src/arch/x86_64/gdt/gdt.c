#include "gdt.h"

static gdtEntry_t gdtEntries[GDT_MAX_DESCRIPTORS];
uint8_t gdtIndexTable = 0;

static void createDescriptor(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    // ! todo: error message
    if(gdtIndexTable >= GDT_MAX_DESCRIPTORS) return;
    if(limit > 0xFFFFF) return;
    
    gdtEntries[gdtIndexTable].limitLow = GDT_LIMIT_LOW(limit);
    gdtEntries[gdtIndexTable].baseLow = GDT_BASE_LOW(base);
    gdtEntries[gdtIndexTable].baseMiddle = GDT_BASE_MIDDLE(base);
    gdtEntries[gdtIndexTable].access = access;
    gdtEntries[gdtIndexTable].limitHigh = GDT_LIMIT_HIGH(limit);
    gdtEntries[gdtIndexTable].flags = flags;
    gdtEntries[gdtIndexTable].baseHigh = GDT_BASE_HIGH(base);

    gdtIndexTable++;
}

void initGDT() {
    gdtRegister_t gdtReg;
    gdtReg.size = sizeof(gdtEntry_t) * GDT_MAX_DESCRIPTORS - 1;
    gdtReg.addr = (uint64_t) &gdtEntries;

    // null descriptor
    createDescriptor(0, 0, 0, 0);

    // kernel mode code descriptor
    createDescriptor(0, 0xFFFFF, 
        GDT_ACCESS_IS_PRESENT | GDT_ACCESS_CODE_SEGMENT | GDT_ACCESS_CODE_IS_READABLE | GDT_ACCESS_CODE_IS_EXECUTABLE | GDT_ACCESS_RING0,
        GDT_FLAGS_IS_64BITS | GDT_FLAGS_GRANULARITY_4KIB
    );

    // kernel mode data descriptor
    createDescriptor(0, 0xFFFFF, 
        GDT_ACCESS_IS_PRESENT | GDT_ACCESS_DATA_SEGMENT | GDT_ACCESS_DATA_IS_WRITABLE | GDT_ACCESS_RING0,
        GDT_FLAGS_IS_64BITS | GDT_FLAGS_GRANULARITY_4KIB
    );

    loadGDT(&gdtReg);
}