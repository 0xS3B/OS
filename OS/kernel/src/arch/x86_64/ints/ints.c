#include "ints.h"

#include <system.h>
#include <arch/x86_64/io/io.h>

isr_t interruptHandlers[MAX_INTERRUPTS];

static const char* exceptionMessages[MAX_EXCEPTIONS] = {
    "Division Error", // no error code
    "Debug",
    "Non-Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault", // ! todo: error type
    "Reserved",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    "Reserved",
};

bool isRegistered(uint8_t intNum) {
    return (interruptHandlers[intNum] != NULL);
}

void interruptsHandler(registers_t* regs) {
    if(regs->interruptNumber < MAX_EXCEPTIONS) {
        exceptionsHandler(regs);
    } else if(regs->interruptNumber > MAX_EXCEPTIONS && regs->interruptNumber < MAX_IRQS) { // for IRQs
        if(isRegistered(regs->interruptNumber)) {
            // call irq handler
            interruptHandlers[regs->interruptNumber](regs);
        }

        // send an EOI (end of interrupt) to the PIC
        ioWrite8(0x20, 0x20);
    }
}

void exceptionsHandler(registers_t* regs) {
    if(regs->errorCode == false)
        log(LOG_INFO, "Interrupt exception", "%s (%d)", exceptionMessages[regs->interruptNumber], regs->interruptNumber);
    else {
        log(LOG_ERROR, "Interrupt exception", "%s (%d)", exceptionMessages[regs->interruptNumber], regs->interruptNumber);
    
        if((regs->cs & 0b11) == KERNEL_RING) {
            while(true) {
                asm("hlt");
            }
        }
    }
}

void registerInterruptHandler(uint8_t intNum, isr_t handler) {
    interruptHandlers[intNum] = handler;
}