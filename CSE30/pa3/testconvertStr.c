/*
 * Filename: testconvertStr.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: Unit test program to test the function convertStr.c
 * Date: May/15/2018
 * Sources of Help: ManPage
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"

#define SUPERLONG "9999999999999999999999999999999999999999999999999"
#define VALIDNUM "12"
#define VALID 12
/*
 * Unit Test for convertStr.c 
 *
 * long convertStr( char * str, int * errorFlag );
 *
 */
void testconvertStr() {

  // declare a error flag
  int errorFlag;
  int ret;

  // test case that str is a valid num
  char * str = VALIDNUM;
  ret = convertStr(str,&errorFlag);
  TEST(ret == VALID && errorFlag == 0);

  // test case that str is a valid num
  str = "1";
  ret = convertStr(str,&errorFlag);
  TEST(ret == 1 && errorFlag == 0);

  // test case that str is not valid num
  str = "1a";
  ret = convertStr(str,&errorFlag);
  TEST(ret == -1 && errorFlag == 1);

  // test case that str is not valid num
  str = "ca";
  ret = convertStr(str,&errorFlag);
  TEST(ret == -1 && errorFlag == 1);

  // test case that str is not a valid num
  str = SUPERLONG; 
  ret = convertStr(str,&errorFlag);
  TEST(ret == -1 && errorFlag == 1);
}

/*
 * main driver for the testing 
 *
 */
int main() {
  (void) fprintf( stderr, "Testing ...\n\n" );
  testconvertStr();
  (void) fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
