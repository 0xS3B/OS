#include <log/log.h>

#include <print.h>

void log(LOG_LEVEL level, const char* module, const char* str, ...) {
    char strBuffer[1024];
    
    va_list args;
    va_start(args, str);

    vprintf(strBuffer, sizeof(strBuffer), str, args);

    va_end(args);

    switch (level)
    {
        case SUCCESS:
            serialPrint("\033[1;32m[SUCCESS]\033[1;0m");
            break;

        case INFO:
            serialPrint("\033[1;36m[INFO]\033[1;0m");
            break;
        
        case WARN:
            serialPrint("\033[1;33m[WARN]\033[1;0m");
            break;

        case ERROR:
            serialPrint("\033[1;31m[ERROR]\033[1;0m");
            break;

        default:
            break;
    }
    serialWrite(' ');

    if(module) {
        serialPrint(module);
        serialPrint(": ");
    }

    serialPrint(strBuffer);
    serialWrite('\n');
}