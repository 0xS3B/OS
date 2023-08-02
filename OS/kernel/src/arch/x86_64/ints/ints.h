#pragma once

#include <types.h>

#define MAX_INTERRUPTS       256

typedef struct {
    uint64_t rdi, rsi, rbp, rdx, rcx, rbx, rax;
    uint64_t interruptNumber, errorCode;
    uint64_t rip, cs, rflags, rsp, ss;
} __attribute__((packed)) registers_t;

extern uint64_t interruptVectors[MAX_INTERRUPTS];