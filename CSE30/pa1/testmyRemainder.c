/*
 * Filename: testmyRemainder.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: Unit test program to test the function myRemainder.
 * Date: April/16/2018
 * Sources of Help: Manpage
 */ 

#include <stdio.h>

#include "pa1.h"
#include "test.h"

/*
 * Unit Test for myRemainder.s
 * long myRemainder( long dividend, long divisor ); 
 *
 * get the remainder after the division
 *
 * Returns the remainder.
 */
void testmyRemainder( ) {

  /* Test dividend bigger than diviosr */
  TEST( myRemainder( 5, 3 ) == 2 );

  /* Test dividend equal to diviosr */
  TEST( myRemainder( 5, 5 ) == 0 );

  /* Test dividend smaller than divisor*/
  TEST( myRemainder( 2, 5 ) == 2 );
  /*
   * Some things to think about are error cases, extreme cases, normal cases,
   * abnormal cases, etc.
   */
}


int main( void ) {

  fprintf(stderr, "Running tests for myRemainder...\n");
  testmyRemainder();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
