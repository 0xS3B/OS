#pragma once

#include <types.h>

// x86 in/out instructions

static inline void ioWrite8(uint16_t port, uint8_t data){
    __asm__ volatile("outb %b0, %w1" : : "a" (data), "Nd" (port));
}

static inline void ioWrite16(uint16_t port, uint16_t data){
    __asm__ volatile("outw %w0, %w1" : : "a" (data), "Nd" (port));
}

static inline void ioWrite32(uint16_t port, uint32_t data){
	__asm__ volatile("outl %0, %w1" : : "a" (data), "Nd" (port));
}


static inline uint8_t ioRead8(uint16_t port){
    uint8_t data;
    __asm__ volatile("inb %w1, %b0" : "=a" (data) : "Nd" (port));
    return data;
}

static inline uint16_t ioRead16(uint16_t port){
    uint16_t data;
    __asm__ volatile("inw %w1, %w0" : "=a" (data) : "Nd" (port));
    return data;
}

static inline uint32_t ioRead32(uint16_t port){
    uint32_t data;
    __asm__ volatile("inl %w1, %0" : "=a" (data) : "Nd" (port));
    return data;
}