#include "ints.h"

#include <log/log.h>

const char* exceptionMessages[32] = {

};

void interruptHandler() {
    log(SUCCESS, NULL, "interrupt!!!");
}