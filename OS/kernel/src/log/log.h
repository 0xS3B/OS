#pragma once

#include <types.h>

#include <drivers/serial/serial.h>

typedef enum {
    SUCCESS     = 0,
    INFO        = 1,
    WARN        = 2,
    ERROR       = 3,
} LOG_LEVEL;

void log(LOG_LEVEL level, const char* module, const char* str, ...);