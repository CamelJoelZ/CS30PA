/*
 * Filename: main.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: tick the clock  
 * Date: May/06/2018
 * Sources of Help: Manpage
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "pa2.h"
#include "pa2Strings.h"



#define LEN 6
/*
 * Main driver for the program 
 *
 * int main( int argc, char *argv[] );
 */

int main( int argc, char *argv[] ){
  unsigned char clock[CLOCK_ARR_SIZE] = {0}; 
  // check for right num of args
  if(argc > MAX_ARGS){
    fprintf(stderr,STR_USAGE,argv[0],MIN_TICKS,MAX_TICKS,DEF_TICKS,
    MIN_HR,MAX_HR,MIN_MIN,MAX_MIN,MIN_SEC,MAX_SEC);
    return EXIT_FAILURE;
  }
  
  // check for help flag
  if((argc == MIN_ARGS) && strncmp(argv[HELP_INDEX],STR_HELP,LEN + 1) == 0){
    printf(STR_USAGE,argv[0],MIN_TICKS,MAX_TICKS,DEF_TICKS,
    MIN_HR,MAX_HR,MIN_MIN,MAX_MIN,MIN_SEC,MAX_SEC);
    return EXIT_SUCCESS;
  }
   
  int flag = 0;
  // check for numTick
  long numTicks;
  if(argc == 1){
    // secify numTick if user does not enter it
    numTicks = DEF_TICKS;
  }
  else{
    char *ptr;
    errno = 0;
    numTicks = strtol(argv[NUM_TICKS_INDEX], &ptr, BASE);
    if(*ptr != '\0' || errno != 0){
      fprintf(stderr,STR_TICK_PARSE_ERR);
      flag = 1;
    }
    if(isInRange(numTicks,MIN_TICKS,MAX_TICKS) != 1 && errno == 0){
      fprintf(stderr,STR_TICKS_RANGE_ERR,(int)numTicks,MIN_TICKS,MAX_TICKS);
      flag = 1;
    }
  }

  // check for startTime 
  struct timeval first;
  struct tm *second;
  struct tInfo third;
  // case that no startTime entered
  if(argc != MAX_ARGS){
    timeRightNow( &first, '\0'); 
    const time_t time = first.tv_sec;
    second = localtime( &time );
    convertTime( &third, second);
  }
  // startTime was specified as the second command line arg 
  else{
    unsigned long ret;
    ret = interpretTime( &third, argv[START_TIME_INDEX]);

    // error check
    if( ret != 0) flag = 1;

    if( (ret & ERR_TIME_FORMAT) == ERR_TIME_FORMAT) 
      fprintf(stderr,STR_TIME_FORMAT_ERR);
    if( (ret & ERR_TIME_NUM) == ERR_TIME_NUM ) 
      fprintf(stderr,STR_TIME_PARSE_ERR);
    if( (ret & ERR_TIME_RANGE) == ERR_TIME_RANGE)
      fprintf(stderr,STR_TIME_RANGE_ERR);
  }
  if( flag == 1){
    // print out usage and return fail
    fprintf(stderr,STR_USAGE,argv[0],MIN_TICKS,MAX_TICKS,DEF_TICKS,
    MIN_HR,MAX_HR,MIN_MIN,MAX_MIN,MIN_SEC,MAX_SEC);

    return EXIT_FAILURE;
  }
  // if no error parsing args
  else{

    // starttime not specified 
    if(argc != MAX_ARGS){
      char *toPrint = asctime(second); 
      printf("%s\n",toPrint);
    }

    // set up the clock
    setClock(clock, &third);

    // prin out the clock
    printClock(clock);

    // tick and print again
    for( int q = 0; q < numTicks; q++){
      tickClock(clock);
      printClock(clock);
    }

    return EXIT_SUCCESS;
  }

}
