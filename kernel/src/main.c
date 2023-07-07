#include "../../bootloader/limine/limine.h"

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

void kernel_start() {
    struct limine_terminal_response *reponse = terminal_request.response;
    
    reponse->write(reponse->terminals[0], "Hello World!", 12);

    while(1) asm("hlt");
}