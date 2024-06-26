#include "gdt.h"

#include <system.h>

#define MODULE_NAME "GDT"

static __attribute__((aligned(8))) gdt_t gdt;
static tss_t tss = {
    .reserved0 = 0,
    .rsp = {},
    .reserved1 = 0,
    .ist = {},
    .reserved2 = 0,
    .reserved3 = 0,
    .iopbOffset = 0,
};

static gdt_entry_t gdt_createDescriptor(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    gdt_entry_t descriptor;
    
    descriptor.limitLow = GDT_LIMIT_LOW(limit);
    descriptor.baseLow = GDT_BASE_LOW(base);
    descriptor.baseMiddle = GDT_BASE_MIDDLE(base);
    descriptor.access = access;
    descriptor.limitHigh = GDT_LIMIT_HIGH(limit);
    descriptor.flags = flags;
    descriptor.baseHigh = GDT_BASE_HIGH(base);

    return descriptor;
}

static tss_entry_t tss_createDescriptor(uint64_t base, uint32_t limit) {
    tss_entry_t tssDescriptor;
    
    tssDescriptor.limitLow = GDT_LIMIT_LOW(limit);
    tssDescriptor.baseLow = GDT_BASE_LOW(base);
    tssDescriptor.baseMiddle = GDT_BASE_MIDDLE(base);
    tssDescriptor.access = GDT_ACCESS_IS_PRESENT | GDT_ACCESS_IS_ACCESSED | GDT_ACCESS_IS_EXECUTABLE;
    tssDescriptor.limitHigh = GDT_LIMIT_HIGH(limit);
    tssDescriptor.flags = GDT_FLAG_IS_64BITS;
    tssDescriptor.baseHigh = GDT_BASE_HIGH(base);
    tssDescriptor.baseUpper = GDT_BASE_UPPER(base);
    tssDescriptor.reserved = 0;

    return tssDescriptor;
}

void gdt_init() {
    // INSTALL GDT
    // kernel null descriptor
    gdt.gdtEntries[0] = gdt_createDescriptor(0, 0, 0, 0);

    // kernel code descriptor
    gdt.gdtEntries[1] = gdt_createDescriptor(0, 0xFFFFF, 
        GDT_ACCESS_IS_PRESENT | GDT_ACCESS_CODEDATA_SEGMENT | GDT_ACCESS_READ_WRITE | GDT_ACCESS_IS_EXECUTABLE | GDT_ACCESS_RING0,
        GDT_FLAG_IS_64BITS | GDT_FLAG_GRANULARITY_4KIB
    );

    // kernel data descriptor
    gdt.gdtEntries[2] = gdt_createDescriptor(0, 0xFFFFF, 
        GDT_ACCESS_IS_PRESENT | GDT_ACCESS_CODEDATA_SEGMENT | GDT_ACCESS_READ_WRITE | GDT_ACCESS_RING0,
        GDT_FLAG_IS_64BITS | GDT_FLAG_GRANULARITY_4KIB
    );

    // user code descriptor
    gdt.gdtEntries[3] = gdt_createDescriptor(0, 0xFFFFF, 
        GDT_ACCESS_IS_PRESENT | GDT_ACCESS_CODEDATA_SEGMENT | GDT_ACCESS_READ_WRITE | GDT_ACCESS_IS_EXECUTABLE | GDT_ACCESS_RING3,
        GDT_FLAG_IS_64BITS | GDT_FLAG_GRANULARITY_4KIB
    );

    // user data descriptor
    gdt.gdtEntries[4] = gdt_createDescriptor(0, 0xFFFFF, 
        GDT_ACCESS_IS_PRESENT | GDT_ACCESS_CODEDATA_SEGMENT | GDT_ACCESS_READ_WRITE | GDT_ACCESS_RING3,
        GDT_FLAG_IS_64BITS | GDT_FLAG_GRANULARITY_4KIB
    );

    gdt.tssEntry = tss_createDescriptor((uint64_t)&tss, sizeof(tss_t));
    
    gdt_register_t gdtReg = { 
        .size = sizeof(gdt_t) - 1,
        .addr = (uint64_t) &gdt,
    };
    gdt_load(&gdtReg);
    tss_load();

    log(LOG_SUCCESS, MODULE_NAME, "Initialized");
}