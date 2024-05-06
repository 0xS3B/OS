#pragma once

#include <stdint.h>

#define PIC1_OFFSET     0x20
#define PIC2_OFFSET     0x28

void picSendEOI(uint8_t intNum);