#pragma once

#include <types.h>

#include <arch/arch.h>

#define COM1_PORT       0x3F8

typedef enum {
    // when DLAB is disabled
    IER_REG         = COM1_PORT + 1, // Interrupt Enable Register

    // when DLAB is enabled
    DLL_REG         = COM1_PORT + 0, // Divisor Latch Low Register
    DLH_REG         = COM1_PORT + 1, // Divisor Latch High Register

    LCR_REG         = COM1_PORT + 3, // Line Control Register
    IIR_FIFO_REG    = COM1_PORT + 2, // Interrupt ID (r/o) and FIFO Control (w/o) Registers
    MCR_REG         = COM1_PORT + 4, // Modem Control Register
} UART_REGISTERS;

typedef enum {
    // data bits (bit 0 and 1)
    LCR_DATA_8BITS      = ((1 << 0) | (1 << 1)),

    // stop bits (bit 2)
    LCR_ONE_STOPBIT     = NULL, // if data > 5bits

    // parity bits (bit 3, 4 and 5)
    LCR_NO_PARITY       = NULL,

    // DLAB (divisor latch access bit) (bit 7)
    LCR_ENABLE_DLAB     = (1 << 7),
} LCR_BITS;

typedef enum {
    FCR_ENABLE_FIFO         = (1 << 0),
    FCR_CLEAR_RCV           = (1 << 1), // Clear Receiver FIFO
    FCR_CLEAR_TST           = (1 << 2), // Clear Transmitter FIFO
    FCR_RFTL_14BYTES        = ((1 << 6) | (1 << 7)), // Receiver FIFO Trigger Level (when the buffer is full (14 bytes))
} FCR_BITS; // write only

typedef enum {
    MCR_DTR         = (1 << 0), // Data Terminal Ready
    MCR_RTS         = (1 << 1), // Request To Send
    MCR_OUT1        = (1 << 2), // OUT1 (unused in PC implementations)
    MCR_OUT2        = (1 << 3), // OUT2 (enable irq in PC implementations)
} MCR_BITS;

void initSerial();

void serialWrite(char c);
void serialPrint(const char* c);