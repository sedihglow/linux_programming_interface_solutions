/*
    Macros and definitions i use in various programs
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

#define FAILURE -1
#define SUCCESS 0

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

                    /* other */

/* Create a bit mask for a given range of bits. start, end. (lsb,msb).
   - start   == int, Which bit from bit 0 to start the mask.
   - end     == int, Which bit greater than start to end the mask.
   - resMask == int, Where the resulting bit mask will be placed */
#define CREATE_MASK(start, end, resMask)                                       \
({                                                                             \
    int __INC_ = 0;                                                            \
    if((start) < (end))                                                        \
        errmsg("create_mask: start > end, no mask was generated.");            \
                                                                               \
    resMask = 0; /* just to make sure im not an idiot when i call this */      \
    for(__INC_ = (start); __INC_ <= (end); ++__INC_){                          \
        (resMask) |= 1 << __INC_;}                                             \
}) /* end CREATE_MASK */

/* TODO: Adjust this macro or make an alternate that can call a function with
         variable arguments, rather than just one argument. (i.e. free(pntr);) */
/* vectorizes a function funct, its C99 as fuck tho.
   -Type is the type of pointer used. (VA_ARGS could be void for example.). 
   -... is a variable argument list.
   -will execute every argument into the function.
   -funct only takes in one argument. */
#define APPLY_FUNCT(type, funct, ...)                                          \
({                                                                              \
    void *stopper = (int[]){0};                                                \
    type **apply_list = (type*[]){__VA_ARGS__, stopper};                       \
    int __i_;                                                                  \
                                                                               \
    for(__i_ = 0; apply_list[__i_] != stopper; ++__i_){                        \
        (funct)(apply_list[__i_]);}                                            \
}) /* end apply_funct */
    
/* apply free to every pointer given in the argument list using the
   apply_funct macro */
#define FREE_ALL(...)   APPLY_FUNCT(void, free, __VA_ARGS__)
#endif
