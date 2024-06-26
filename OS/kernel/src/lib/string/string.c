#include "string.h"

void itoa(char* buffer, int num, uint8_t base) {
    int i = 0;
    int isNegative = 0;

    if(num == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return;
    }

    if(num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }

    while(num != 0) {
        int rem = num % base;
        buffer[i++] = (rem < 10) ? ('0' + rem) : ('A' + rem - 10);
        num /= base;
    }

    if(isNegative)
        buffer[i++] = '-';

    buffer[i] = '\0';


    // Reverse buffer
    int start = 0;
    int end = i - 1; // length

    while(start < end) {
        char temp = buffer[start];

        buffer[start] = buffer[end];
        buffer[end] = temp;

        start++;
        end--;
    }
}

int strncmp(const char *s1, const char *s2, size_t n) {
    for(size_t i = 0; i < n; ++i) {
        if(s1[i] != s2[i]) {
            return (uint8_t)s1[i] - (uint8_t)s2[i];
        }

        if(s1[i] == '\0') {
            return 0;
        }
    }
    return 0;
}