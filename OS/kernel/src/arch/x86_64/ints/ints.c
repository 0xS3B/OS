#include "ints.h"

#include <log/log.h>

const char* exceptionMessages[32] = {

};

void interruptHandler(registers_t* registers) {
    log(SUCCESS, NULL, "interrupt n°%d", registers->interruptNumber); 
}