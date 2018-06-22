/*
 * Filename: tickClock.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: tick the clock  
 * Date: April/29/2018
 * Sources of Help: Manpage
 */ 

#include "pa2.h"
#include "test.h"
#include "pa2Strings.h"

#define FOUR 4
/*
 * tick the time and chang it accordingly
 *
 * void tickClock( unsigned char clock[] );
 */


void tickClock( unsigned char clock[] ){
  unsigned char result;
  
  // deal with special case before anything
  if(clock[HR_INDEX] == 0x11 && clock[MIN_INDEX] == 0x59 
  && clock[SEC_INDEX] == 0x59){
    if(clock[AM_PM_INDEX] == 'A') clock[AM_PM_INDEX] = 'P';
    else clock[AM_PM_INDEX] = 'A';
  }

  // tick the sec ones 
  result = tickOne(SEC_INDEX, MAX_ONES_SEC, clock);

  // check for sec tens 
  if(result == 0){
    result = tickTens(SEC_INDEX, MAX_TENS_SEC, clock);
    //check for minute ones
    if(result == 0){
      result = tickOne(MIN_INDEX, MAX_ONES_MIN, clock);
      //check for minute tens
      if(result == 0){
        result = tickTens(MIN_INDEX, MAX_TENS_MIN, clock);
        //check for hour ones
        if(result == 0){
          result = tickOne(HR_INDEX, MAX_ONES_HR, clock);
          //check for hour tens
          if(result == 0){
            result = tickTens(HR_INDEX, MAX_TENS_HR, clock);
          }
        }
      }
    }
  }
}

unsigned char tickOne(int index, int max, unsigned char clock[]){

  unsigned char extracted;
  unsigned char result;

  // extract the ones
  extracted = clock[index] & ONES_BITMASK;
  // increment the ones
  result = incrementClockValue(extracted, max);
  
  // update the ones place
  clock[index] &= TENS_BITMASK;
  clock[index] ^= result;
  
  return result;
}

unsigned char tickTens(int index, int max, unsigned char clock[]){
    
  unsigned char extracted;
  unsigned char result;
  
  // manipulate the tens place to call increment func
  extracted = clock[index] >> FOUR;
  // increment tens place
  result = incrementClockValue(extracted, max);
  // manipulate back the tens place
  result = result << FOUR;
  // store the sec back to the clock
  clock[index] = result;

  return result;
}
