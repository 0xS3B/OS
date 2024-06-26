#ifndef TYPES_H
#define TYPES_H 

#include <stdint.h>

#define NULL    0

typedef __SIZE_TYPE__ size_t;

typedef enum {
    false,
    true
} bool;

typedef __builtin_va_list	va_list;
#define va_start(v,l)		__builtin_va_start(v,l)
#define va_end(v)			__builtin_va_end(v)
#define va_arg(v,l)			__builtin_va_arg(v,l)
#define va_copy(d,s)		__builtin_va_copy(d,s)

#endif