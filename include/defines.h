#ifndef DEFINES_H
#define DEFINES_H

#define TRUE 1
#define FALSE 0

#define GUARD_OOB(val, min, max)                do { if ((val) < (min) || (val) > (max)) { goto cleanup; } } while (0)
#define GUARD_SUCCESS(expr)                     do { if ((expr) == EXIT_SUCCESS) { goto cleanup; } } while (0)
#define GUARD_FAILURE(expr)                     do { if ((expr) == EXIT_FAILURE) { goto cleanup; } } while (0)
#define GUARD_TRUE(expr)                        do { if ((expr) == TRUE) { goto cleanup; } } while (0)
#define GUARD_FALSE(expr)                       do { if ((expr) == FALSE) { goto cleanup; } } while (0)
#define GUARD_POS(val)                          do { if ((val) > 0) { goto cleanup; } } while (0)
#define GUARD_NEG(val)                          do { if ((val) < 0) { goto cleanup; } } while (0)
#define GUARD_ZERO(val)                         do { if ((val) == 0) { goto cleanup; } } while (0)
#define GUARD_NULL(ptr)                         do { if ((ptr) == NULL) { goto cleanup; } } while (0)
#define GUARD_EQUAL(val1, val2)					do { if ((val1) == (val2)) { goto cleanup; } } while (0)
#define GUARD_NON_POS(val)                      do { if ((val) <= 0) { goto cleanup; } } while (0)
#define GUARD_NON_NEG(val)                      do { if ((val) >= 0) { goto cleanup; } } while (0)
#define GUARD_NON_ZERO(val)                     do { if ((val) != 0) { goto cleanup; } } while (0)
#define GUARD_NON_NULL(ptr)						do { if ((ptr) != NULL) { goto cleanup; } } while (0)
#define GUARD_NON_EQUAL(val1, val2)				do { if ((val1) != (val2)) { goto cleanup; } } while (0)

#define ZERO_MEM(ptr, size)						memset(ptr, 0, size)	
#define FREE(ptr)								if ((ptr)) { free(ptr); ptr = NULL; }

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

#define STATIC_ASSERT(cond, msg) typedef char static_assertion_##msg[(cond) ? 1 : -1]

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

#endif
