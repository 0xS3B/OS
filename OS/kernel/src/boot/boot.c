#include <arch/arch.h>

#include "../../bootloader/limine/limine.h"

#include <log/log.h>

static volatile struct limine_rsdp_request rsdp_request = {
    .id = LIMINE_RSDP_REQUEST,
    .revision = 0
};

extern bool isXSDP;

/* test */
/* void keyboard(registers_t* regs) {
    uint8_t scancode = ioRead8(0x60);
    log(LOG_INFO, "KEYBOARD", "key: %d", scancode);
} */

void kernelStart() {
    ASM_CLR_INT

    serial_init();

    acpi_XSDPHeader_t* xsdpDesc = (acpi_XSDPHeader_t*) rsdp_request.response->address;
    isXSDP = (xsdpDesc->rsdpDesc.revision >= 1);

    log(LOG_INFO, "BOOT [ACPI]", "is XSDP? %d, RSDP Valid? %d", isXSDP, acpi_RSDPChecksumValid(xsdpDesc));

    acpi_SDTHeader_t* MADT = acpi_findTable(xsdpDesc, "APIC");

    arch_init();
    
    //asm("int $0xE");

    //registerInterruptHandler(IRQ(1), &keyboard);

    while(1) ASM_HALT;
}