#pragma once

#include <types.h>

#define MAX_INTERRUPTS      256
#define MAX_EXCEPTIONS      32
#define MAX_IRQS            15

#define IRQ(n) (n + 32)

typedef struct {
    uint64_t rdi, rsi, rbp, rdx, rcx, rbx, rax;
    uint64_t interruptNumber, errorCode;
    uint64_t rip, cs, rflags, rsp, ss;
} __attribute__((packed)) registers_t;

typedef void (*isr_t)(registers_t*);

extern uint64_t isrs[MAX_INTERRUPTS];

bool isRegistered(uint8_t intNum);

void registerInterruptHandler(uint8_t intNum, isr_t handler);

void interruptsHandler(registers_t* regs);
void exceptionsHandler(registers_t* regs);