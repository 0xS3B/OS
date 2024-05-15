[bits 64]

%include "src/arch/x86_64/misc/cpu/cpu.inc"

%define MAX_INTERRUPTS 256

extern interruptsHandler
global isrs

isr_common:
    PUSHA64

    cld

    mov rdi, rsp ; put registers as arg (see register_t in ints/ints.h)
    call interruptsHandler

    POPA64

    add rsp, 16 ; remove error code and interrupt number from stack
    iretq


%macro SET_ISR 1
    dq isr%1
%endmacro
isrs:
    %assign i 0
    %rep MAX_INTERRUPTS
        SET_ISR i
    %assign i i+1
    %endrep


%macro ISR_NOERRCODE 1
    isr%1:
        push 0 ; error code? no.
        push %1 ; push interrupt number
        jmp isr_common
%endmacro

%macro ISR_ERRCODE 1
    isr%1:
        ; the error code is pushed by the cpu
        push %1
        jmp isr_common
%endmacro

; exception interrupts
ISR_NOERRCODE   0
ISR_NOERRCODE   1
ISR_NOERRCODE   2
ISR_NOERRCODE   3
ISR_NOERRCODE   4
ISR_NOERRCODE   5
ISR_NOERRCODE   6
ISR_NOERRCODE   7
ISR_ERRCODE     8
ISR_NOERRCODE   9
ISR_ERRCODE     10
ISR_ERRCODE     11
ISR_ERRCODE     12
ISR_ERRCODE     13
ISR_ERRCODE     14
ISR_NOERRCODE   15
ISR_NOERRCODE   16
ISR_ERRCODE     17
ISR_NOERRCODE   18
ISR_NOERRCODE   19
ISR_NOERRCODE   20
ISR_ERRCODE     21
ISR_NOERRCODE   22
ISR_NOERRCODE   23
ISR_NOERRCODE   24
ISR_NOERRCODE   25
ISR_NOERRCODE   26
ISR_NOERRCODE   27
ISR_NOERRCODE   28
ISR_ERRCODE     29
ISR_ERRCODE     30
ISR_NOERRCODE   31

; hardware interrupts and the rest
%assign i 32
%rep MAX_INTERRUPTS - 32
    ISR_NOERRCODE i
%assign i i+1
%endrep