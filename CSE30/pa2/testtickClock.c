/*
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: Unit test program to test the function tickClock.c
 * Date: 04/29/2018
 * Sources of Help: Man Page
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for tickClock.c
 *
 * void tickClock( unsigned char clock[] );
 * 
 * TickClock function will tick the clock and save the result back
 *
 * Purpose: Tests our tickClock implementation by passing a lot of values
 * in as test cases for our function. Tests edge cases like 0:0:0 times, big
 * times, and others.
 */
void testtickClock() {

  // Test 11:59:59 pm which has a lot of carry out
  unsigned char clock[] = {0x11,0x59,0x59,'P'};
  tickClock(clock);
  TEST(clock[HR_INDEX] == 0x12 && clock[MIN_INDEX] == 0 
  && clock[SEC_INDEX] == 0 && clock[AM_PM_INDEX] == 'A');

  // Test 11:59:59 pm which has a lot of carry out
  unsigned char clock1[] = {0x11,0x59,0x59,'A'};
  tickClock(clock1);
  TEST(clock1[HR_INDEX] == 0x12 && clock1[MIN_INDEX] == 0 
  && clock1[SEC_INDEX] == 0 && clock1[AM_PM_INDEX] == 'P');

  // Test 11:44:58 which has no carry out 
  unsigned char clock2[] = {0x11,0x44,0x58,'P'};
  tickClock(clock2);
  TEST(clock2[HR_INDEX] == 0x11 && clock2[MIN_INDEX] == 0x44 
  && clock2[SEC_INDEX] == 0x59 && clock2[AM_PM_INDEX] == 'P');


  // Test 02:44:59 which has carry out from sec to min
  unsigned char clock3[] = {0x2,0x44,0x59,'P'};
  tickClock(clock3);
  TEST(clock3[HR_INDEX] == 0x2 && clock3[MIN_INDEX] == 0x45 
  && clock3[SEC_INDEX] == 0x0 && clock3[AM_PM_INDEX] == 'P');
  
  // Test 02:39:59 which has carry out from sec to tens in min
  unsigned char clock4[] = {0x2,0x39,0x59,'P'};
  tickClock(clock4);
  TEST(clock4[HR_INDEX] == 0x2 && clock4[MIN_INDEX] == 0x40 
  && clock4[SEC_INDEX] == 0x0 && clock4[AM_PM_INDEX] == 'P');
}
int main( void ) {

  fprintf(stderr, "Running tests for tickClock...\n");
  testtickClock();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
