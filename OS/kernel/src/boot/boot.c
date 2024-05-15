#include <arch/arch.h>

#include "../../bootloader/limine/limine.h"

#include <log/log.h>

static volatile struct limine_rsdp_request rsdp_request = {
    .id = LIMINE_RSDP_REQUEST,
    .revision = 0
};

/* test */
/* void keyboard(registers_t* regs) {
    uint8_t scancode = ioRead8(0x60);
    log(LOG_INFO, "KEYBOARD", "key: %d", scancode);
} */

void kernelStart() {
    asm("cli");

    serial_init();

    acpi_SDT_t* sdt;

    acpi_XSDP_t* xsdpDesc = (acpi_XSDP_t*) rsdp_request.response->address; 
    if(xsdpDesc->rsdpDesc.revision == 2) {
        sdt = (acpi_SDT_t*) xsdpDesc->xsdtAddr;
    } else {
        sdt = (acpi_SDT_t*)(uintptr_t) xsdpDesc->rsdpDesc.rsdtAddr;
    }

    log(LOG_INFO, "BOOT [ACPI]", "0x%x", sdt);

    arch_init();
    
    //asm("int $0xE");

    //registerInterruptHandler(IRQ(1), &keyboard);

    while(1) asm("hlt");
}