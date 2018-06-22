/*
 * Filename: printClock.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: print the clock  
 * Date: May/06/2018
 * Sources of Help: Manpage
 */ 

#include "pa2.h"
#include "test.h"
#include "pa2Strings.h"

#define LINE 12
#define FIVE 5
#define TWO 2
#define SHIFT 7
#define MASK 1
#define FOUR 4
#define THREE 3
#define NL "\n"
/*
 * print out the clock string and bit representation
 *
 * void printClock( const unsigned char clock[] );
 */


void printClock( const unsigned char clock[] ){
  // print out the first line
  for(int i = 0; i < LINE; i++){
    printf("%c",clock[AM_PM_INDEX]);
  }
  printf(NL);

  int bit;
  // line between
  for(int j = 0; j < FIVE; j++){
    // first char in a line
    if(j % TWO == 0)
      printf("%c ",CHAR_M);
    else
      printf("%c ",clock[AM_PM_INDEX]);

    // print our a single line 
    for(int k = 0; k < THREE; k++){

      // decimal repre in the second last line
      if(j + 1 == FIVE){
        // print other stuff and break out the loop
        printf("%02x ",clock[HR_INDEX]);  
        printf("%02x ",clock[MIN_INDEX]);  
        printf("%02x ",clock[SEC_INDEX]);  
        break;
      }

      //clock[0] upper nibble bit
      // extract the specific bit
      bit = clock[HR_INDEX + k] >> (SHIFT - j);
      bit &= MASK;
      // print out the bit
      if( bit == 1) 
        printf("%c",CHAR_BIT_SET);
      else
        printf("%c",CHAR_BIT_UNSET);

      // clock[0] lower nibble bit
      // get rid of the upper nibbe
      bit = clock[HR_INDEX + k] << FOUR;
      // extract the certain bit
      bit = bit >> (SHIFT - j);
      bit &= MASK;
      // print out the bit
      if( bit == 1) 
        printf("%c ",CHAR_BIT_SET);
      else
        printf("%c ",CHAR_BIT_UNSET);

    }
    // last char in a line
    if(j % TWO == 0)
      printf("%c",CHAR_M);
    else
      printf("%c",clock[AM_PM_INDEX]);

    printf(NL);
  }

  // print out the last line
  for(int i = 0; i < LINE; i++){
    printf("%c",clock[AM_PM_INDEX]);
  }
  printf(NL);
  printf(NL);
}
