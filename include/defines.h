#ifndef DEFINES_H
#define DEFINES_H

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0  // 0=off, 1=errors, 2=warnings, 3=info, 4=trace
#endif

#ifndef STATIC_ASSERT
#define STATIC_ASSERT(cond, msg) typedef char static_assertion_##msg[(cond) ? 1 : -1]
#endif

typedef unsigned char u8; 
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;
typedef signed char i8; 
typedef signed short i16;
typedef signed int i32;
typedef signed long i64;
typedef float f32;
typedef double f64;
typedef char b8;
typedef int b32;

STATIC_ASSERT(sizeof(u8) == 1, u8_must_be_1_bytes);
STATIC_ASSERT(sizeof(u16) == 2, u16_must_be_2_bytes);
STATIC_ASSERT(sizeof(u32) == 4, u32_must_be_4_bytes);
STATIC_ASSERT(sizeof(u64) == 8, u64_must_be_8_bytes);
STATIC_ASSERT(sizeof(i8) == 1, i8_must_be_1_bytes); 
STATIC_ASSERT(sizeof(i16) == 2, i16_must_be_2_bytes);
STATIC_ASSERT(sizeof(i32) == 4, i32_must_be_4_bytes);
STATIC_ASSERT(sizeof(i64) == 8, i64_must_be_8_bytes);
STATIC_ASSERT(sizeof(f32) == 4, f32_must_be_4_bytes);
STATIC_ASSERT(sizeof(f64) == 8, f64_must_be_8_bytes);
STATIC_ASSERT(sizeof(b8) == 1, b8_must_be_1_bytes);
STATIC_ASSERT(sizeof(b32) == 4, b32_must_be_4_bytes);

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef DEBUG_BREAK
#define DEBUG_BREAK() __builtin_trap()
#endif

static inline void
debug_log(i32 level, const char *file, i32 line, const char *func, const char *fmt, ...)
{
    if (level <= DEBUG_LEVEL) 
	{
        va_list args;
        va_start(args, fmt);
        fprintf(stderr, "[%s:%d in %s] ", file, line, func);
        vfprintf(stderr, fmt, args);
        fputc('\n', stderr);
        va_end(args);
        fflush(stderr);
    }
}

#define DEBUG_BREAK_IF(level, fmt, ...) \
    do { \
        if (level <= DEBUG_LEVEL) { \
            debug_log(level, __FILE__, __LINE__, __func__, fmt, __VA_ARGS__); \
            DEBUG_BREAK(); \
        } \
    } while(0)

#define GUARD_OOB(val, min, max)                do { if ((val) < (min) || (val) > (max)) { DEBUG_BREAK_IF(1, "Out of bounds: %d not in [%d,%d]", (val), (min), (max)); goto cleanup; } } while (0)
#define GUARD_SUCCESS(expr)                     do { if ((expr) == EXIT_SUCCESS) { DEBUG_BREAK_IF(1, "Unexpected success: %s", #expr); goto cleanup; } } while (0)
#define GUARD_FAILURE(expr)                     do { if ((expr) == EXIT_FAILURE) { DEBUG_BREAK_IF(1, "Unexpected failure: %s", #expr); goto cleanup; } } while (0)
#define GUARD_TRUE(expr)                        do { if ((expr) == TRUE) { DEBUG_BREAK_IF(1, "Unexpected TRUE: %s", #expr); goto cleanup; } } while (0)
#define GUARD_FALSE(expr)                       do { if ((expr) == FALSE) { DEBUG_BREAK_IF(1, "Unexpected FALSE: %s", #expr); goto cleanup; } } while (0)
#define GUARD_POS(val)                          do { if ((val) > 0) { DEBUG_BREAK_IF(1, "Unexpected positive: %d", (val)); goto cleanup; } } while (0)
#define GUARD_NEG(val)                          do { if ((val) < 0) { DEBUG_BREAK_IF(1, "Unexpected negative: %d", (val)); goto cleanup; } } while (0)
#define GUARD_ZERO(val)                         do { if ((val) == 0) { DEBUG_BREAK_IF(1, "Unexpected zero: %d", (val)); goto cleanup; } } while (0)
#define GUARD_NULL(ptr)                         do { if ((ptr) == NULL) { DEBUG_BREAK_IF(1, "Unexpected NULL: %s", #ptr); goto cleanup; } } while (0)
#define GUARD_EQUAL(val1, val2)                 do { if ((val1) == (val2)) { DEBUG_BREAK_IF(1, "Unexpected equality: %s == %s", #val1, #val2); goto cleanup; } } while (0)
#define GUARD_NON_POS(val)                      do { if ((val) <= 0) { DEBUG_BREAK_IF(1, "Unexpected non-positive: %d", (val)); goto cleanup; } } while (0)
#define GUARD_NON_NEG(val)                      do { if ((val) >= 0) { DEBUG_BREAK_IF(1, "Unexpected non-negative: %d", (val)); goto cleanup; } } while (0)
#define GUARD_NON_ZERO(val)                     do { if ((val) != 0) { DEBUG_BREAK_IF(1, "Unexpected non-zero: %d", (val)); goto cleanup; } } while (0)
#define GUARD_NON_NULL(ptr)                     do { if ((ptr) != NULL) { DEBUG_BREAK_IF(1, "Unexpected non-NULL: %s", #ptr); goto cleanup; } } while (0)
#define GUARD_NON_EQUAL(val1, val2)             do { if ((val1) != (val2)) { DEBUG_BREAK_IF(1, "Unexpected inequality: %s != %s", #val1, #val2); goto cleanup; } } while (0)

#define ZERO_MEM(ptr, size)						memset(ptr, 0, size)	
#define FREE(ptr)								if ((ptr)) { free(ptr); ptr = NULL; }

#endif
