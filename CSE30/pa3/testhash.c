/*
 * Filename: testhash.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: Unit test program to test the function hash.s.
 * Date: May/15/2018
 * Sources of Help: ManPage
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

/*
 * c version of hash
 *
 * int hash( char const * str );
 */
static int hashC(char const * str){
  int hash = HASH_START_VAL;
  int strLen = strlen(str);
  for( int i = 0; i < strLen; i++ ) {
   hash = hash * HASH_PRIME + str[i];
  }
  return hash;
}
/*
 * Unit Test for hash.s
 *
 * int hash( char const * str );
 *
 */
void testhash() {

  // test for str a single char
  char * str = "d";
  TEST( hash(str) == hashC(str));

  // test for str no content inside quote
  char * str1 = "";
  TEST( hash(str1) == hashC(str1));

  // test for some random value  
  char * str2 = "ABBB";
  TEST( hash(str2) == hashC(str2));

  // test for some random value  
  char * str3 = "kcnkas";
  TEST( hash(str3) == hashC(str3));

  // test for some random value  
  char * str4 = "QWOPR";
  TEST( hash(str4) == hashC(str4));
}

/*
 * main driver for the testing 
 *
 */
int main() {
  (void) fprintf( stderr, "Testing ...\n\n" );
  testhash();
  (void) fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
