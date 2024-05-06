#include <arch/arch.h>

#include <arch/x86_64/ints/ints.h>
#include <log/log.h>

/* test */
void keyboard(registers_t* regs) {
    log(LOG_INFO, "KEYBOARD", "ok");
    /* uint8_t scancode = ioRead8(0x60);
    log(LOG_INFO, "KEYBOARD", "key: %d", scancode); */
}

void kernelStart() {
    asm("cli");

    initSerial();

    initArch();

    //asm("int $0x10");

    registerInterruptHandler(IRQ1, &keyboard);

    while(1) asm("hlt");
}