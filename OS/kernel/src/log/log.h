#pragma once

#include <types.h>

typedef enum {
    LOG_SUCCESS     = 0,
    LOG_INFO        = 1,
    LOG_WARN        = 2,
    LOG_ERROR       = 3,
} LOG_LEVEL;

void log(LOG_LEVEL level, const char* module, const char* str, ...);