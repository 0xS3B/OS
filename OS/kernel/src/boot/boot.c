#include <arch/arch.h>

#include <arch/x86_64/ints/ints.h>
#include <log/log.h>

#include "../../bootloader/limine/limine.h"
static volatile struct limine_terminal_request terminalRequest = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

/* test */
void keyboard(registers_t* regs) {
    uint8_t scancode = ioRead8(0x60);
    log(INFO, NULL, "%d", scancode);
}

void kernel_start() {
    struct limine_terminal_response *reponse = terminalRequest.response;
    // reponse->write(reponse->terminals[0], "Hello World!", 12);

    initSerial();

    initArch();

    registerInterruptHandler(IRQ1, &keyboard);

    while(1) asm("hlt");
}