/*
 * Filename: testrevHash
 * Author: Zhuoer Wen 
 * Userid: cs30xgz
 * Description: Unit test program to test the function revHash().
 * Date: May/29/2018
 * Sources of Help: Man Page
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa4.h"

/* 
 * C version of revHash
 */
static int revHashC(char * src) {
  int hash = HASH_START_VAL;
  int strLen = strlen(src);
  for( int i = strLen - 1; i >= 0; i--){
    hash = hash * HASH_PRIME + src[i];
  }
  return hash;
}

/*
 * Unit Test for revHash.s
 *
 * long revHash( char * src );
 *
 */
void testrevHash() {

  char * src = "ABCD";
  /* Validate the hash value. */
  TEST( revHash(src) == revHashC(src) );
  
  src = "";
  TEST( revHash(src) == revHashC(src) );
  
  /*
   * TODO: YOU MUST WRITE MORE TEST CASES FOR FULL POINTS
   */
  // random value to test revHash
  src = "ssss";
  TEST( revHash(src) == revHashC(src) );

  // random value to test revHash
  src = "k";
  TEST( revHash(src) == revHashC(src) );

  // random value to test revHash
  src = "##";
  TEST( revHash(src) == revHashC(src) );

  // random value to test revHash
  src = "okk";
  TEST( revHash(src) == revHashC(src) );
}

/*
 * Main driver for the tester
 */
int main() {
  fprintf( stderr, "Testing revHash...\n\n" );
  testrevHash();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
