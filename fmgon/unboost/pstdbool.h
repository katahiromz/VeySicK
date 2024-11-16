/* pstdbool.h --- Unboost portable stdbool.h */
/* Written by katahiromz <katayama.hirofumi.mz@gmail.com>. */
/* You can use this as replacement of <stdbool.h> and <cstdbool>. */
/* This file is public domain software (PDS). */

#ifndef UNBOOST_PSTDBOOL_H
#define UNBOOST_PSTDBOOL_H     1   /* Version 1 */

#ifndef __bool_true_false_are_defined
    #ifdef __cplusplus
        /* already defined */
    #elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
        #include <stdbool.h>
    #else
        #define true        1
        #define false       0
        typedef char        bool;
    #endif
    #define __bool_true_false_are_defined 1
#endif  /* ndef __bool_true_false_are_defined */

#endif  /* ndef UNBOOST_PSTDBOOL_H */
