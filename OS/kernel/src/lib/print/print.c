#include <print.h>
#include <string.h>

uint32_t vprintf(char* buffer, const char* fmt, va_list args) {
    char c;
	char* str = NULL;

    uint32_t index = 0;
	while((c = *fmt++) != 0) {
		if(c == '%') {
			c = *fmt++;

			switch (c)
            {
                case 'p':
                case 'x':
                    itoa(str, va_arg(args, int), 16);
                    
                    goto string;
                    break;

                case 'd':
                case 'i':
                    itoa(str, va_arg(args, int), 10);

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

		if(c == '\0') {
            buffer[index] = '\0';
            break;
        }
	}


    return index;
}