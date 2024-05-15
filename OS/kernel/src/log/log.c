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
        case LOG_SUCCESS:
            serial_print("\033[1;92m[SUCCESS]\033[1;0m");
            break;

        case LOG_INFO:
            serial_print("\033[1;96m[INFO]\033[1;0m");
            break;
        
        case LOG_WARN:
            serial_print("\033[1;93m[WARN]\033[1;0m");
            break;

        case LOG_ERROR:
            serial_print("\033[1;91m[ERROR]\033[1;0m");
            break;

        default:
            break;
    }
    serial_write(' ');

    if(module) {
        serial_print("\033[1;3m");
        serial_print(module);
        serial_print(": ");
        serial_print("\033[1;0m");
    }

    serial_print(strBuffer);
    serial_write('\n');
}