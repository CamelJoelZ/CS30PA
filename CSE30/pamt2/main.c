/*
 * Filename: main.c
 * Author: Zhuoer Wen 
 * Userid: cs30xgz
 * Description: main driver to run the program
 * Date: May/31/2018
 * Sources of Help: Man Page
 */

#include <errno.h>

#include "pamt2.h"

#define BASE 10

/*
 * Function name: main()
 * Function prototype: int main( int argc, char *argv[] );
 * Description: Main driver to run the program 
 * Parameters: int argc, char *argv[]
 * Side Effects: None
 * Error Conditions: None.
 * Return Value: 0 indicating successful execution.
 */

int main( int argc, char *argv[] ) {

  if ( argc < 2 ) {
    (void) fprintf( stderr, "\nUsage: %s num1 [num2 num3 ...]\n\n", argv[0] );
    exit( -1 );
  }

  double startTime, endTime;
  double seqTime;
  long long int factors;

  /* Convert each command-line arg to a long long int */
  char *endptr;

  for ( int i = 1; i < argc; i++ ) {
    errno = 0;
    long long int num = strtoll( argv[i], &endptr, BASE );

    if ( num > MAX_NUM_TO_RUN ) {
      (void) fprintf( stderr, "\nSkipping %s\n", argv[i] );
      (void) fprintf( stderr, "num should be less than or equal to %lld\n\n",
			      MAX_NUM_TO_RUN );
      continue;
    }

    if ( errno != 0 || *endptr != '\0' ) {
      (void) fprintf( stderr, "\nSkipping %s\n", argv[i] );
      (void) fprintf( stderr, "not a valid long long int\n\n" );
      continue;
    }

    /* First do sequential numOfFactors */

    (void) printf( "\nCalculating number of factors for %lld with sequential "
		   "numOfFactors()\n  [be patient with large values]\n", num );

    startTime = omp_get_wtime();
    factors = numOfFactors( num, 2, num + 1 );
    endTime = omp_get_wtime();

    seqTime = endTime - startTime;

    (void) printf( "%lld %s prime\n", num, (factors == 2 ? "is" : "is not") );
    (void) printf( "Number of factors: %lld\n", factors );
    (void) printf( "Completed in %f sec\n\n", seqTime );

    /*
     * After numOfFactors (serial).
     * TODO: Comment out the return 0; below to continue to the next
     *       phase involving parallelizing numOfFactors.c
     */

    //return 0;

    /* Next do parallel numOfFactors using OpenMP directives */

    double parTime;

    (void) printf( "Calculating number of factors for %lld with parallel "
		   "numOfFactors()\n  [be less patient]\n", num );

    /* Print number of threads on this system. Just thread #0 prints vs. all. */
    #pragma omp parallel
    {
      if ( omp_get_thread_num() == 0 ) {
	(void) printf( "Num of threads = %d\n", omp_get_num_threads() );
      }
    }

    startTime = omp_get_wtime();
    factors = parallel_numOfFactors( num, 2, num + 1 );
    endTime = omp_get_wtime();

    parTime = endTime - startTime;

    (void) printf( "%lld %s prime\n", num, (factors == 2 ? "is" : "is not") );
    (void) printf( "Number of factors: %lld\n", factors );
    (void) printf( "Completed in %f sec\n\n", parTime );

    (void) printf( "*** numOfFactors Speed-up: %f ***\n\n", seqTime / parTime );
  }

  return 0;
}

