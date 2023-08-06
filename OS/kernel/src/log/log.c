#include <log/log.h>
#include <drivers/serial/serial.h>

#include <print.h>

void log(LOG_LEVEL level, const char* module, const char* str, ...) {
    char strBuffer[4096];
    
    va_list args;
    va_start(args, str);

    vprintf(strBuffer, sizeof(strBuffer), str, args);

    va_end(args);

    switch (level)
    {
        case SUCCESS:
            serialPrint("\033[1;92m[SUCCESS]\033[1;0m");
            break;

        case INFO:
            serialPrint("\033[1;96m[INFO]\033[1;0m");
            break;
        
        case WARN:
            serialPrint("\033[1;93m[WARN]\033[1;0m");
            break;

        case ERROR:
            serialPrint("\033[1;91m[ERROR]\033[1;0m");
            break;

        default:
            break;
    }
    serialWrite(' ');

    if(module) {
        serialPrint("\033[1;3m");
        serialPrint(module);
        serialPrint(": ");
        serialPrint("\033[1;0m");
    }

    serialPrint(strBuffer);
    serialWrite('\n');
}