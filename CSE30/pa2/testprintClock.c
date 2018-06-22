/*
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: Unit test program to test the function setClock.s
 * Date: 05/06/2018
 * Sources of Help: Man Page
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for printClock.s
 *
 */
void testprintClock() {
  
  const unsigned char clock[4] = {0x08,0x56,0x37,'A'};
  printClock(clock);
  
  
}

int main( void ) {

  fprintf(stderr, "Running tests for setClock...\n");
  testprintClock();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
