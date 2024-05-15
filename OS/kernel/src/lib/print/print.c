#include <print.h>
#include <string.h>

size_t vprintf(char* buffer, size_t bufferSize, const char* fmt, va_list args) {
    char c;
	char num[20];
    char* str = NULL;

    size_t index = 0;
	while((c = *fmt++) != 0) {
		if(c == '%') {
			c = *fmt++; // get the type

			switch (c)
            {
                case 'p':
                case 'x':
                    itoa(num, va_arg(args, int), 16);
                    str = num;
                    
                    goto string;
                    break;

                case 'd':
                case 'i':
                    itoa(num, va_arg(args, int), 10);
                    str = num;

                    goto string;
                    break;

                case 's':
                    str = va_arg(args, char*);

                    string:
                        while(*str) {
                            buffer[index++] = *str++;
                        }
                    break;

                default:
                    break;
			}
		} else {
			buffer[index++] = c;
		}

		if(index > bufferSize)
            break;
	}

    buffer[index] = '\0';

    return index;
}