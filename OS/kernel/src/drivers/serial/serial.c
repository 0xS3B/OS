#include "serial.h"

#include <arch/include.h>
#include ARCH_INCLUDE(misc/asm.h)

#include <log/log.h>
#define MODULE_NAME "Serial Port"

void serial_init() {
    // for UART controller

    io_write8(IER_REG, NULL); // disable interrupt

    // Line control 
    io_write8(LCR_REG, LCR_ENABLE_DLAB); // enable DLAB to access the divisor registers
    io_write8(DLL_REG, 0x3); // set Divisor Latch Low to 3 (115200hz / 3 = 38400hz)
    io_write8(DLH_REG, 0x0);
    io_write8(LCR_REG, LCR_DATA_8BITS | LCR_ONE_STOPBIT | LCR_NO_PARITY);

    // FIFO control
    io_write8(IIR_FIFO_REG, FCR_ENABLE_FIFO | FCR_CLEAR_RCV | FCR_CLEAR_TST | FCR_RFTL_14BYTES);
    
    // Modem control
    io_write8(MCR_REG, MCR_DTR | MCR_RTS | MCR_OUT1 | MCR_OUT2);

    // clear
    serial_print("\033[2J"); // clear screen
    serial_print("\033[H"); // move cursor to upper left corner

    log(LOG_SUCCESS, MODULE_NAME, "Initialized");
}

void serial_write(char c) {
    // QEMU
    io_write8(COM1_PORT, c);
}

void serial_print(const char* c) {
     for(uint64_t i = 0; c[i] != '\0'; i++){
        serial_write(c[i]);

        if(c[i] == '\n') serial_write('\r');   
    }
}