/*
 * Filename: testevenOddHash.c
 * Author: Zhuoer Wen 
 * Userid: cs30xgz
 * Description: Unit test program to test the function evenOddHash().
 * Date: May/29/2018
 * Sources of Help: Man Page
 */

#include <string.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa4.h"

/*
 * Unit Test for evenOddHash.c
 *
 * int evenOddHash( char * str ); 
 *
 */
void testevenOddHash() {
  // random value to test evenOddHash 
  char * src = "okk";
  TEST( evenOddHash(src) == 713208 );

  // random value to test evenOddHash 
  src = "";
  TEST( evenOddHash(src) == 11);

  // random value to test evenOddHash 
  src = "iasbf";
  TEST( evenOddHash(src) == 965538852);

  // random value to test evenOddHash 
  src = "giao";
  TEST( evenOddHash(src) == 25969819);

  // random value to test evenOddHash 
  src = "wu";
  TEST( evenOddHash(src) == 19579);

  // random value to test evenOddHash 
  src = "lio";
  TEST( evenOddHash(src) == 709247);

  // random value to test evenOddHash 
  src = "lid";
  TEST( evenOddHash(src) == 708840);
}

/*
 * Main driver for the tester
 */
int main() {
  fprintf( stderr, "Testing ...\n\n" );
  testevenOddHash();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
