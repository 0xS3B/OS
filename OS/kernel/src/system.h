#pragma once

#include <log/log.h>

typedef enum {
    KERNEL_RING = 0,
    USER_RING   = 3,
} PRIVILEGE_LEVEL;