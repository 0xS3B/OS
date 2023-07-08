#pragma once

#define NULL 0x0

typedef enum {
    false = 0,
    true = 1
} bool;


typedef signed char                 int8_t;
typedef short int                   int16_t;
typedef int                         int32_t;

#if __WORDSIZE == 64
typedef long int                    int64_t;
#else
typedef long long int               int64_t;
#endif

/* Unsigned */
typedef unsigned char               uint8_t;
typedef unsigned short int          uint16_t;
typedef unsigned int                uint32_t;

#if __WORDSIZE == 64
typedef unsigned long int           uint64_t;
#else
typedef unsigned long long int      uint64_t;
#endif

#if defined(__LP64__) || defined(_LP64)
typedef uint64_t uintptr_t;
#else
typedef uint32_t uintptr_t;
#endif

typedef long unsigned int           size_t;
typedef uint64_t                    size64_t;


typedef __builtin_va_list	va_list;
#define va_start(v,l)		__builtin_va_start(v,l)
#define va_end(v)			__builtin_va_end(v)
#define va_arg(v,l)			__builtin_va_arg(v,l)
#define va_copy(d,s)		__builtin_va_copy(d,s)