/*
 * Filename: testgetTableIndex
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: Unit test program to test the function getTableindex.s.
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
 * c version of getTableIndex
 * int hash( char const * str );
 *
 */
static int getTableIndexC(char const * name, size_t tableSize){
  int hashKey = hashC(name);
  if(hashKey < 0) hashKey = hashKey * (-1);
  int index = hashKey % tableSize;
  return index;
}

/*
 * Unit Test for hash.s
 *
 * int hash( char const * str );
 *
 */
void testgetTableIndex() {
  
  // testing random value
  char * str = "ABCD";
  size_t size = 10;
  TEST( getTableIndex(str, size) == getTableIndexC(str, size));
  
  // testing random value
  str = "ac";
  size = 20;
  TEST( getTableIndex(str, size) == getTableIndexC(str, size));
  
  // testing random value
  str = "Aaaa";
  size = 30;
  TEST( getTableIndex(str, size) == getTableIndexC(str, size));

  // testing random value
  str = "c";
  size = 50;
  TEST( getTableIndex(str, size) == getTableIndexC(str, size));

  // testing random value
  str = "k";
  size = 10;
  TEST( getTableIndex(str, size) == getTableIndexC(str, size));
}

/*
 * main driver for the testing 
 *
 */
int main() {
  (void) fprintf( stderr, "Testing ...\n\n" );
  testgetTableIndex();
  (void) fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
