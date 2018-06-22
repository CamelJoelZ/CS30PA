/*
 * Filename: testisEven.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: Unit test program to test the function isEven.
 * Date: April/16/2018
 * Sources of Help: Manpage
 */ 

#include <stdio.h>

#include "pa1.h"
#include "test.h"

/*
 * Unit Test for isEven.s
 *
 * long isEven( long value );
 * check if the value is even 
 *
 * Returns 0 for odd, 1 for even.
 */
void testisEven( ) {

  /* Test for even number*/
  TEST( isEven( 2 ) == 1 );

  /* Test for odd number*/
  TEST( isEven( 1 ) == 0 );

  /* Test for 0*/
  TEST( isEven( 0 ) == 1 );

  /*
   * Some things to think about are error cases, extreme cases, normal cases,
   * abnormal cases, etc.
   */
}


int main( void ) {

  fprintf(stderr, "Running tests for isEven...\n");
  testisEven();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
