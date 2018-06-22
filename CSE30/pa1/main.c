/*
 * Filename: main.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: main driver for program 
 * Date: April/16/2018
 * Sources of Help: Manpage
 */ 

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "pa1.h"
#include "test.h"
#include "pa1Strings.h"


#define ARGNUM 5
#define NL "\n"
/*
 * Main driver and parsing for program
 *
 * int main( int argc, char *argv[] );
 */


int main( int argc, char * argv[] ) {
  
  // check num of args
  if(argc != ARGNUM){
    fprintf(stderr,STR_USAGE,argv[0],HEIGHT_MIN,HEIGHT_MAX,ASCII_MIN,ASCII_MAX,
    ASCII_MIN,ASCII_MAX,ASCII_MIN,ASCII_MAX);
    return EXIT_FAILURE;
  }

  /*
   * parse height
   */
  errno = 0;
  
  int exitFlag = 0;
  int heightErr = 0;

  char * ptr;
  long height = strtol(argv[1], &ptr, BASE); // parse out the height 
    
  // error converting to long
  if(errno != 0){
    // set the flag
    heightErr = 1;
    exitFlag = 1;
    // declare a array to hold erro message
    char result[BUFSIZ];
    snprintf(result,BUFSIZ,STR_ERR_CONVERTING,STR_HEIGHT,argv[1],BASE);
    perror(result);
    fprintf(stderr,NL);
  }
  
  // height contains non-numerical char
  if(heightErr != 1 && *ptr != '\0'){
    // set the flag
    heightErr = 1;
    exitFlag = 1;
    // print out error message
    fprintf(stderr,STR_ERR_NOT_INT,STR_HEIGHT,argv[1]);
    fprintf(stderr,NL);
  }
  
  // height is not in range
  if(heightErr != 1 && isInRange(height,HEIGHT_MIN,HEIGHT_MAX+1) != 1){
    // set the flag
    exitFlag = 1;
    fprintf(stderr,STR_ERR_NUM_RANGE,STR_HEIGHT,height,HEIGHT_MIN,HEIGHT_MAX);
    fprintf(stderr,NL);
  }
  
  // height is not odd
  if(heightErr != 1 && isEven(height) == 1){
    // set the flag
    heightErr = 1;
    exitFlag = 1;
    // error msg
    fprintf(stderr,STR_ERR_ODD,STR_HEIGHT,height);
    fprintf(stderr,NL);

  }

  /*
   * parse border char
   */
  int borderErr = 0;

  // not a single char
  if(strlen(argv[2]) != 1){
    // set error flag
    borderErr = 1;
    exitFlag = 1;

    // error msg
    fprintf(stderr,STR_ERR_SINGLE_CHAR,STR_BORDER_CHAR,argv[2]);
    fprintf(stderr,NL);
  }
  
  // char not in range
  if(borderErr != 1 && isInRange(argv[2][0],ASCII_MIN,ASCII_MAX) != 1){
    // set the flag
    exitFlag = 1;
    // error msg
    fprintf(stderr,STR_ERR_ASCII_RANGE,STR_BORDER_CHAR,argv[2][0],
    ASCII_MIN,ASCII_MAX);  
    fprintf(stderr,NL);
  }

  /*
   * parse filler char
   */
  int fillerErr = 0;

  // not a single char
  if(strlen(argv[3]) != 1){
    // set error flag
    fillerErr = 1;
    exitFlag = 1;

    // error msg
    fprintf(stderr,STR_ERR_SINGLE_CHAR,STR_FILLER_CHAR,argv[3]);
    fprintf(stderr,NL);
  }
  
  // char not in range
  if(fillerErr != 1 && isInRange(argv[3][0],ASCII_MIN,ASCII_MAX) != 1){
    // set the flag
    exitFlag = 1;
    // error msg
    fprintf(stderr,STR_ERR_ASCII_RANGE,STR_FILLER_CHAR,argv[3][0],ASCII_MIN
    ,ASCII_MAX);  
    fprintf(stderr,NL);
  }


  /*
   * parse bowtie char
   */
  int bowtieErr = 0;

  // not a single char
  if(strlen(argv[4]) != 1){
    // set error flag
    bowtieErr = 1;
    exitFlag = 1;

    // error msg
    fprintf(stderr,STR_ERR_SINGLE_CHAR,STR_BOWTIE_CHAR,argv[4]);
    fprintf(stderr,NL);
  }
  
  // char not in range
  if(bowtieErr != 1 && isInRange(argv[4][0],ASCII_MIN,ASCII_MAX) != 1){
    // set the flag
    exitFlag = 1;
    // error msg
    fprintf(stderr,STR_ERR_ASCII_RANGE,STR_BOWTIE_CHAR,argv[4][0],ASCII_MIN,
    ASCII_MAX);  
    fprintf(stderr,NL);
  }

  // return exit_failure if any error occurs
  if(exitFlag == 1) return EXIT_FAILURE;

  /*
  * check 3 chars are not the same 
  */
  // border and bowtie
  if(argv[2][0] == argv[4][0]){
    fprintf(stderr,STR_ERR_BORDER_BOWTIE_DIFF,argv[2][0],argv[4][0]);
    fprintf(stderr,NL);
    return EXIT_FAILURE;
  }

  // filler and bowtie
  if(argv[3][0] == argv[4][0]){
    fprintf(stderr,STR_ERR_FILLER_BOWTIE_DIFF,argv[3][0],argv[4][0]);
    fprintf(stderr,NL);
    return EXIT_FAILURE;
  }
  
  // no error and print out the figure
  displayBowtie(height,argv[2][0],argv[3][0],argv[4][0]);
  return EXIT_SUCCESS;
}
