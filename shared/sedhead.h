/*
    stuff i use for stuff.


    I really want to know how i should handle increments in for loops in 
    my macros.
        Have them pass an increment variable?
                         ||
        Have the mixed declaration and declare it with random __'s.

    I just need to research how mixed declarations are implemented by
    the compilers that do it, and how certian standards handle it.
*/

#ifndef _SED_HEAD_
#define _SED_HEAD_

#include <sys/types.h>
#include <stdio.h>                  
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <getopt.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <pthread.h>

/*#define NDEBUG*/
#include <assert.h>

#include "err_handle/err_handle.h"  /* Error handling functions. */
#include "get_num/get_num.h"        /* Convert strings to int types. */

/* Use memcpy to set a float value, causing the proper value to appear instead
   of the min/max. (example: Nan, -Nan, etc.), (memset gives improper results) */
#define SET_FLOAT(num, set)    memcpy(&num, &set, sizeof(num))
#define SET_DOUBLE(num, set)   SET_FLOAT(num,set)
#define SET_NAN(num, set)      SET_FLOAT(num, set)
#define SET_INF(num, set)      SET_FLOAT(num,set)

/* Use these definitions placed in memory for the above macros in set.
 * example: int32_t fnan = PF_NAN;
 *          int64_t dnegInf = ND_INF;
 *
 *          set_float(num, fnan);
 *          set_double(num, dneginf); 
 */

/* 32 bit float */
#define PF_NAN  0x7fc00000    /* positive NAN */
#define NF_NAN  0xffc00000    /* negetive NAN */

#define PF_INF  0x7f800000    /* positive INF */
#define NF_INF  0xff800000    /* negetive INF */

/* 64 bit double */
#define PD_NAN  0x7ff8000000000000    /* positive NAN */
#define ND_NAN  0xfff8000000000000    /* negetive NAN */

#define PD_INF  0x7ff0000000000000    /* positive INF */
#define ND_INF  0xfff0000000000000    /* negetive INF */

                    /* __restrict */
#define Restrict __restrict

                    /* bool */
#ifndef __SED_BOOL_
#define __SED_BOOL_
    #ifdef true 
    #undef true
    #endif
    #ifdef false 
    #undef false 
    #endif
    typedef enum {false, true} Bool;
#endif

                    /* min/max */
#define MIN(m,n) ((m) < (n) ? (m) : (n))
#define MAX(m,n) ((m) > (n) ? (m) : (n))

/* Get a single character from stdin and loop untill input is correct. 
   NOTE: > sets the single character to a capital letter.
         > uses the above macro GET_CHAR(input), not getchar from the standard
           lib. 
           TODO: I will consider changing GET_CHARs name in the future
   - input  == char , string to check for Y/N.
   - string == char*, message to print to the user via printf();.
   - ...    == ending variable length arguments placed in printf(string,...);. */
#define YES_NO(input, string, ...)                                             \
{                                                                              \
    /* TODO: Find out what happens with a statment like the following:         \
             assert("Some literal string" != NULL);                            \
             - It doesn have an address... but is it NULL? awkward statment. */\
    do                                                                         \
    {                                                                          \
        printf((string), __VA_ARGS__);                                         \
        GET_CHAR(input);                                                       \
        (input) = toupper((input));                                            \
    }while(input != 'Y' && input != 'N');                                      \
} /* end YES_NO */

                    /* other */

/* Create a bit mask for a given range of bits. start, end. (lsb,msb).
   - start   == int, Which bit from bit 0 to start the mask.
   - end     == int, Which bit greater than start to end the mask.
   - resMask == int, Where the resulting bit mask will be placed */
#define CREATE_MASK(start, end, resMask)                                       \
{                                                                              \
    int __INC_ = 0;                                                            \
    if((start) < (end)){                                                       \
        errmsg("create_mask: start > end, no mask was generated.");}           \
                                                                               \
    resMask = 0; /* just to make sure im not an idiot when i call this */      \
    for(__INC_ = (start); __INC_ <= (end); ++__INC_){                          \
        (resMask) |= 1 << __INC_;}                                             \
} /* end CREATE_MASK */

/* TODO: Adjust this macro or make an alternate that can call a function with
         variable arguments, rather than just one argument. (i.e. free(pntr);) */
/* vectorizes a function funct, its C99 as fuck tho.
   -Type is the type of pointer used. (VA_ARGS could be void for example.). 
   -... is a variable argument list.
   -will execute every argument into the function.
   -funct only takes in one argument. */
#define APPLY_FUNCT(type, funct, ...)                                          \
{                                                                              \
    void *stopper = (int[]){0};                                                \
    type **apply_list = (type*[]){__VA_ARGS__, stopper};                       \
    int __i_;                                                                  \
                                                                               \
    for(__i_ = 0; apply_list[__i_] != stopper; ++__i_){                        \
        (funct)(apply_list[__i_]);}                                            \
} /* end apply_funct */
    
/* apply free to every pointer given in the argument list using the
   apply_funct macro */
#define FREE_ALL(...)   APPLY_FUNCT(void, free, __VA_ARGS__)
#endif
