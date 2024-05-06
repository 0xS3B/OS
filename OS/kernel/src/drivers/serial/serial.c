#include "serial.h"

#include <log/log.h>
#define MODULE_NAME "Serial Port"

void initSerial() {
    // for UART controller

    ioWrite8(IER_REG, NULL); // disable interrupt

    // Line control 
    ioWrite8(LCR_REG, LCR_ENABLE_DLAB); // enable DLAB to access the divisor registers
    ioWrite8(DLL_REG, 0x3); // set Divisor Latch Low to 3 (115200hz / 3 = 38400hz)
    ioWrite8(DLH_REG, 0x0);
    ioWrite8(LCR_REG, LCR_DATA_8BITS | LCR_ONE_STOPBIT | LCR_NO_PARITY);

    // FIFO control
    ioWrite8(IIR_FIFO_REG, FCR_ENABLE_FIFO | FCR_CLEAR_RCV | FCR_CLEAR_TST | FCR_RFTL_14BYTES);
    
    // Modem control
    ioWrite8(MCR_REG, MCR_DTR | MCR_RTS | MCR_OUT1 | MCR_OUT2);

    // clear
    serialPrint("\033[2J"); // clear screen
    serialPrint("\033[H"); // move cursor to upper left corner

    log(LOG_SUCCESS, MODULE_NAME, "Initialized");
}

void serialWrite(char c) {
    // QEMU
    ioWrite8(COM1_PORT, c);
}

void serialPrint(const char* c) {
     for(uint64_t i = 0; c[i] != '\0'; i++){
        serialWrite(c[i]);

        if(c[i] == '\n') serialWrite('\r');   
    }
}