#include "gdt.h"

#include <log/log.h>
#define MODULE_NAME "GDT"

static gdtEntry_t gdtEntries[GDT_MAX_DESCRIPTORS];
static tss_t tss = {
    .reserved0 = 0,
    .rsp = {},
    .reserved1 = 0,
    .ist = {},
    .reserved2 = 0,
    .reserved3 = 0,
    .iopbOffset = 0,
};

static gdtEntry_t createDescriptor(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    gdtEntry_t descriptor;
    
    descriptor.limitLow = GDT_LIMIT_LOW(limit);
    descriptor.baseLow = GDT_BASE_LOW(base);
    descriptor.baseMiddle = GDT_BASE_MIDDLE(base);
    descriptor.access = access;
    descriptor.limitHigh = GDT_LIMIT_HIGH(limit);
    descriptor.flags = flags;
    descriptor.baseHigh = GDT_BASE_HIGH(base);

    return descriptor;
}

static void createTSSDescriptor(uint64_t base, uint32_t limit) {
    tssEntry_t* tssDescriptor = (tssEntry_t*) &gdtEntries[5];
    
    tssDescriptor->limitLow = GDT_LIMIT_LOW(limit);
    tssDescriptor->baseLow = GDT_BASE_LOW(base);
    tssDescriptor->baseMiddle = GDT_BASE_MIDDLE(base);
    tssDescriptor->access = GDT_ACCESS_IS_PRESENT | GDT_ACCESS_IS_ACCESSED | GDT_ACCESS_IS_EXECUTABLE;
    tssDescriptor->limitHigh = GDT_LIMIT_HIGH(limit);
    tssDescriptor->flags = GDT_FLAGS_IS_64BITS;
    tssDescriptor->baseHigh = GDT_BASE_HIGH(base);
    tssDescriptor->baseUpper = GDT_BASE_UPPER(base);
    tssDescriptor->reserved = 0;
}

void initGDT() {
    // INSTALL GDT
    // kernel null descriptor
    gdtEntries[0] = createDescriptor(0, 0, 0, 0);

    // kernel code descriptor
    gdtEntries[1] = createDescriptor(0, 0xFFFFF, 
        GDT_ACCESS_IS_PRESENT | GDT_ACCESS_CODEDATA_SEGMENT | GDT_ACCESS_READ_WRITE | GDT_ACCESS_IS_EXECUTABLE | GDT_ACCESS_RING0,
        GDT_FLAGS_IS_64BITS | GDT_FLAGS_GRANULARITY_4KIB
    );

    // kernel data descriptor
    gdtEntries[2] = createDescriptor(0, 0xFFFFF, 
        GDT_ACCESS_IS_PRESENT | GDT_ACCESS_CODEDATA_SEGMENT | GDT_ACCESS_READ_WRITE | GDT_ACCESS_RING0,
        GDT_FLAGS_IS_64BITS | GDT_FLAGS_GRANULARITY_4KIB
    );

    // user code descriptor
    gdtEntries[3] = createDescriptor(0, 0xFFFFF, 
        GDT_ACCESS_IS_PRESENT | GDT_ACCESS_CODEDATA_SEGMENT | GDT_ACCESS_READ_WRITE | GDT_ACCESS_IS_EXECUTABLE | GDT_ACCESS_RING3,
        GDT_FLAGS_IS_64BITS | GDT_FLAGS_GRANULARITY_4KIB
    );

    // user data descriptor
    gdtEntries[4] = createDescriptor(0, 0xFFFFF, 
        GDT_ACCESS_IS_PRESENT | GDT_ACCESS_CODEDATA_SEGMENT | GDT_ACCESS_READ_WRITE | GDT_ACCESS_RING3,
        GDT_FLAGS_IS_64BITS | GDT_FLAGS_GRANULARITY_4KIB
    );

    createTSSDescriptor((uint64_t)&tss, sizeof(tss_t));
    
    gdtRegister_t gdtReg = { 
        .size = sizeof(gdtEntries) - 1,
        .addr = (uint64_t) &gdtEntries,
    };
    loadGDT(&gdtReg);
    loadTSS();

    log(SUCCESS, MODULE_NAME, "Initialized");
}