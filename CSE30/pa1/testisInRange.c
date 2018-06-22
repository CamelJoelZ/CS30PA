/*
 * Filename: testisInRange.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: Unit test program to test the function isInRange.
 * Date: April/16/2018
 * Sources of Help: Manpage
 */ 

#include <stdio.h>

#include "pa1.h"
#include "test.h"

/*
 * Unit Test for isInRange.s
 *
 * long isInRange( long value, long minRange, long maxRange );
 *
 * Checks to see if value is within the range of minRange (inclusive)
 * to maxRange (exclusive).
 *
 * Returns -1 if minRange >= maxRange.
 * Returns 1 if value is between minRange (inclusive) and maxRange.
 * Returns 0 otherwise.
 */
void testisInRange( ) {

  /* Test value in range */
  TEST( isInRange( 0, 0, 1 ) == 1 );
  TEST( isInRange( 2, 1, 3 ) == 1 );

  /* Test error with range values */
  TEST( isInRange( 2, 3, 1 ) == -1 );
  TEST( isInRange( 2, 3, 3 ) == -1 );

  /* Test values not within range */
  TEST( isInRange( 0, 1, 3 ) == 0 );
  TEST( isInRange( 4, 1, 3 ) == 0 );
  TEST( isInRange( 3, 1, 3 ) == 0 );

  /*
   * Some things to think about are error cases, extreme cases, normal cases,
   * abnormal cases, etc.
   */
}


int main( void ) {

  fprintf(stderr, "Running tests for isInRange...\n");
  testisInRange();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
