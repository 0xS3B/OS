#include <arch/arch.h>

#include <log/log.h>

#include "../../bootloader/limine/limine.h"
static volatile struct limine_terminal_request terminalRequest = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

void kernel_start() {
    struct limine_terminal_response *reponse = terminalRequest.response;
    // reponse->write(reponse->terminals[0], "Hello World!", 12);

    initSerial();

    initArch();

    while(1) asm("hlt");
}