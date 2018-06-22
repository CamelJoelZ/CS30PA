/*
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: Unit test program to test the function incrementCLockValue 
 * Date: 04/29/2018
 * Sources of Help: Man Page
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for incrementClockValue.s
 *
 * unsigned char incrementClockValue( unsigned char BCDbits,
 *   const unsigned int maxValue );
 *
 *
 * Purpose: Tests our incrementClockValue implementation by passing 
 *   a variety of values in as test cases for our function. normal 
 *   times, larger times, and others.
 */
void testincrementClockValue() {
  unsigned char bcdBits;
  unsigned char result;
  // test for value with no carry out
  bcdBits = 7;
  result = incrementClockValue(bcdBits, MAX_ONES_SEC);
  TEST( result == 8 );

  // test for value with carry out
  bcdBits = 9;
  result = incrementClockValue(bcdBits, MAX_ONES_SEC);
  TEST( result == 0 );

  // test for value with carry out
  bcdBits = 5;
  result = incrementClockValue(bcdBits, MAX_TENS_SEC);
  TEST( result == 0 );

  // test for value with no carry out
  bcdBits = 4;
  result = incrementClockValue(bcdBits, MAX_TENS_SEC);
  TEST( result == 5 );
}

int main( void ) {

  fprintf(stderr, "Running tests ...\n");
  testincrementClockValue();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
