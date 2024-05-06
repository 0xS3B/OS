#pragma once

#include <types.h>

#define MAX_INTERRUPTS      256
#define MAX_EXCEPTIONS      32
#define MAX_IRQS            15

#define IRQ0    32
#define IRQ1    33
#define IRQ2    34
#define IRQ3    35
#define IRQ4    36
#define IRQ5    37
#define IRQ6    38
#define IRQ7    39
#define IRQ8    40
#define IRQ9    41
#define IRQ10   42
#define IRQ11   43
#define IRQ12   44
#define IRQ13   45
#define IRQ14   46
#define IRQ15   47

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