/*
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: Unit test program to test the function interpretTime 
 * Date: 04/29/2018
 * Sources of Help: Man Page
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for interpretTime.c
 *
 * unsigned long interpretTime( struct tInfo * tInfoPtr, 
 *  const char * time );
 *
 * Purpose: Tests our interpretTime implementation by passing 
 *   a variety of values in as test cases for our function. normal 
 *   times, larger times, and others.
 */
void testinterpretTime() {
  // Declare our struct tInfo to hold our times
  struct tInfo time;
  unsigned long result;

  // Set the times to all 0 for a zeroed out test
  time.tm_sec = 0;
  time.tm_min = 0;
  time.tm_hour = 0;
  time.am_pm = 'A';
  
  // error time format 1
  result = interpretTime(&time, "03:05:aA");
  TEST(result == ERR_TIME_FORMAT);
  
  // error time format 2
  result = interpretTime(&time, "1z0:16y20");
  TEST(result == ERR_TIME_FORMAT);

  // error time format 3
  result = interpretTime(&time, "12:03:05b");
  TEST(result == ERR_TIME_FORMAT);

  // error time format 4
  result = interpretTime(&time, "12:03:05a9");
  TEST(result == ERR_TIME_FORMAT);

  // error time format 5
  result = interpretTime(&time, "12:03:05");
  TEST(result == ERR_TIME_FORMAT);

  // error time range
  result = interpretTime(&time, "13:03:05p");
  TEST(result == ERR_TIME_RANGE);

  // error time range
  result = interpretTime(&time, "12:66:05p");
  TEST(result == ERR_TIME_RANGE);

  // error time range
  result = interpretTime(&time, "12:03:60p");
  TEST(result == ERR_TIME_RANGE);

  // error time format and error time num
  result = interpretTime(&time, "1g2:03:05");
  TEST(result == (ERR_TIME_FORMAT | ERR_TIME_NUM));

  // error time format and error time num and err range
  result = interpretTime(&time, "12a:66:05");
  TEST(result == (ERR_TIME_FORMAT | ERR_TIME_NUM | ERR_TIME_RANGE));

  // correct time passed in 
  result = interpretTime(&time, "12:03:22p");
  TEST(result == 0 && time.tm_sec == 22 && time.tm_min == 3 
        && time.tm_hour == 12 && time.am_pm == 'p');
  
  // special case 00:xx:xx 
  result = interpretTime(&time, "00:03:22p");
  TEST(result == 0 && time.tm_sec == 22 && time.tm_min == 3 
        && time.tm_hour == 12 && time.am_pm == 'p');
  
} 

int main( void ) {

  fprintf(stderr, "Running tests ...\n");
  testinterpretTime();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
