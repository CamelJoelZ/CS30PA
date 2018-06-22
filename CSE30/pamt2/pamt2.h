#ifndef PAMT2_H    /* Macro Guard */
#define PAMT2_H

#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

/*
 * Set some maximum value to perform factoring, say 2^32, otherwise it will
 * take too long.
 */

// #define MAX_NUM_TO_RUN (4294967296LL * 2)
#define MAX_NUM_TO_RUN (1LL << 33)

/*
 * Local function prototypes for PAMT2
 */

long long numOfFactors( long long n,
                        long long lo,
                        long long hi );

long long parallel_numOfFactors( long long n,
                                 long long lo,
                                 long long hi );

#endif

