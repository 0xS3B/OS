#include "idt.h"

#include <log/log.h>
#define MODULE_NAME "IDT"

static __attribute__((aligned(8))) idtEntry_t idtEntries[IDT_MAX_GATES];

// todo
static idtEntry_t setIDTGate() {

}

void initIDT() {
    

    idtRegister_t idtReg = {
        .size = sizeof(idtEntries) - 1,
        .addr = (uint64_t) &idtEntries,
    };
    loadIDT(&idtReg);

    log(SUCCESS, MODULE_NAME, "Initialized");
}