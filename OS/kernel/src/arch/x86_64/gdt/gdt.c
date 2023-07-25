#include "gdt.h"

#include <log/log.h>
#define MODULE_NAME "GDT"

gdt_t gdt;
tss_t tss = {
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

static tssEntry_t createTSSDescriptor(uint64_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    tssEntry_t descriptor;
    
    descriptor.limitLow = GDT_LIMIT_LOW(limit);
    descriptor.baseLow = GDT_BASE_LOW(base);
    descriptor.baseMiddle = GDT_BASE_MIDDLE(base);
    descriptor.access = access;
    descriptor.limitHigh = GDT_LIMIT_HIGH(limit);
    descriptor.flags = flags;
    descriptor.baseHigh = GDT_BASE_HIGH(base);
    descriptor.baseUpper = GDT_BASE_UPPER(base);
    descriptor.reserved = 0;

    return descriptor;
}

void initGDT() {
    // INSTALL GDT
    // kernel null descriptor
    gdt.gdtEntries[0] = createDescriptor(0, 0, 0, 0);

    // kernel code descriptor
    gdt.gdtEntries[1] = createDescriptor(0, 0xFFFFF, 
        GDT_ACCESS_IS_PRESENT | GDT_ACCESS_CODEDATA_SEGMENT | GDT_ACCESS_READ_WRITE | GDT_ACCESS_IS_EXECUTABLE | GDT_ACCESS_RING0,
        GDT_FLAGS_IS_64BITS | GDT_FLAGS_GRANULARITY_4KIB
    );

    // kernel data descriptor
    gdt.gdtEntries[2] = createDescriptor(0, 0xFFFFF, 
        GDT_ACCESS_IS_PRESENT | GDT_ACCESS_CODEDATA_SEGMENT | GDT_ACCESS_READ_WRITE | GDT_ACCESS_RING0,
        GDT_FLAGS_IS_64BITS | GDT_FLAGS_GRANULARITY_4KIB
    );

    // user code descriptor
    gdt.gdtEntries[3] = createDescriptor(0, 0xFFFFF, 
        GDT_ACCESS_IS_PRESENT | GDT_ACCESS_CODEDATA_SEGMENT | GDT_ACCESS_READ_WRITE | GDT_ACCESS_IS_EXECUTABLE | GDT_ACCESS_RING3,
        GDT_FLAGS_IS_64BITS | GDT_FLAGS_GRANULARITY_4KIB
    );

    // user data descriptor
    gdt.gdtEntries[4] = createDescriptor(0, 0xFFFFF, 
        GDT_ACCESS_IS_PRESENT | GDT_ACCESS_CODEDATA_SEGMENT | GDT_ACCESS_READ_WRITE | GDT_ACCESS_RING3,
        GDT_FLAGS_IS_64BITS | GDT_FLAGS_GRANULARITY_4KIB
    );
    
    gdtRegister_t gdtReg = { 
        .size = sizeof(gdtEntry_t) * GDT_MAX_DESCRIPTORS - 1,
        .addr = (uint64_t) &gdt.gdtEntries,
    };
    loadGDT(&gdtReg);

    // INSTALL TSS
    gdt.tssEntry = createTSSDescriptor(&tss, sizeof(tss_t), 
        GDT_ACCESS_IS_PRESENT | GDT_ACCESS_IS_ACCESSED | GDT_ACCESS_IS_EXECUTABLE,
        GDT_FLAGS_IS_64BITS
    );

    loadTSS();

    log(SUCCESS, MODULE_NAME, "Initialized");
}