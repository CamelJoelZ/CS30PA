/*
 * Filename: create.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Descriptions is the main driver for the create portion of the program.
 *            
 * Date: June/02/2018
 * Sources of Help: Manpage
 */ 

#include <getopt.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include "pa4.h"
#include "pa4Strings.h"
#define BASE 0
#define REQUIRED_NUM 2

/*
 * Function Name: create.c 
 *
 * Function Prototype: int main( int argc, char * argv[] ); 
 *
 * Description:This is the main driver for the create portion your program.
 *              Its main tasks are to parse the command line  arguments, 
 *              build the hashtables of email data, and serialize the 
 *              hashtables to a file. 
 *            
 *
 * Parameters: int argc, char * argv[] ; 
 * Side Effects: print out usage and error message accordingly 
 * Error Condition: 1. command line args error
 *                  2. missing infile flag or output flag 
 *                  3. extra arguments after getopt_long 
 *                  4. dynamic memory allocation fail
 * Return Value: EXIT_SUCCESS on success and EXIT_FAILURE on any error. 
 *
 */
int main( int argc, char * argv[] ){
  // Parsing command line arguments
  int command;
  long size = DEFAULT_SIZE;
  char errorMsg[BUFSIZ];
  int fileFlagNum = 0;
  char * end;
  FILE * fp;
  FILE * output;

  // flag struct
  static struct option long_options[] =
  {
      {LONG_HELP_FLAG,  optional_argument, NULL, HELP_FLAG},
      {LONG_SIZE_FLAG,  optional_argument, NULL, SIZE_FLAG},
      {LONG_INFILE_FLAG,required_argument, NULL, INFILE_FLAG},
      {LONG_OUTPUT_FLAG,required_argument, NULL, OUTPUT_FLAG},
      {0,        0,                 0,     0}
  };

  while(1){
    // parse the command 
    command = getopt_long(argc,argv,CREATE_FLAGS,long_options,NULL);

    // check if out of commands 
    if(command == -1) break;

    // check what command it is
    switch(command){
   
      case HELP_FLAG:
        printf(LONG_CREATE_USAGE);
        return EXIT_SUCCESS;

      case SIZE_FLAG:  
        // check if there is a arguments
        if(optarg == 0){
          size = DEFAULT_SIZE;
          break;
        }
        
        errno = 0;
        long ret = strtol(optarg,&end,BASE);
        
        // not ending with 0/
        if(*end != '\0'){
          fprintf(stderr,INVALID_NUM,optarg);
          fprintf(stderr,SHORT_CREATE_USAGE);
          return EXIT_FAILURE;
        }

        // size number too large
        if(errno != 0 || ret == 0){
          snprintf(errorMsg,BUFSIZ,TOO_LARGE_NUM,optarg,0);
          perror(errorMsg);
          fprintf(stderr,SHORT_CREATE_USAGE);
          return EXIT_FAILURE;
        }

        // size is not within range
        long range = isInRange(ret,MIN_SIZE,MAX_SIZE + 1);
        if(range != 1){
          
          fprintf(stderr,TABLE_SIZE_ERR,MIN_SIZE,MAX_SIZE);
          fprintf(stderr,SHORT_CREATE_USAGE);
          return EXIT_FAILURE;
        }

        // valid size
        size = ret;
        break;

      case INFILE_FLAG:
        errno = 0;
        // try to open the file 
        fp = fopen(optarg,"r");
        
        // error opening the file
        if(errno != 0 || fp == NULL){
          perror(FILTER_ERR);
          fprintf(stderr,SHORT_CREATE_USAGE);
          return EXIT_FAILURE;
        }
        // increment the fileFlagnum
        fileFlagNum++;
        break;

      case OUTPUT_FLAG:
        // try to open the ouput file
        errno = 0;
        output = fopen(optarg,"w");
        // error opening the file
        if(errno != 0 || output == NULL){
          perror(WTABLE_FILE_ERR);
          fprintf(stderr,SHORT_CREATE_USAGE);
          return EXIT_FAILURE;
        }
        // increment the fileFlagnum
        fileFlagNum++;
        break;

      // invalid flag
      default:
        fprintf(stderr,SHORT_CREATE_USAGE);
        return EXIT_FAILURE;
        
    }
  }
  // missing either of infile or output flag
  if(fileFlagNum != REQUIRED_NUM){
    fprintf(stderr,ARG_ERR);
    fprintf(stderr,SHORT_CREATE_USAGE);
    return EXIT_FAILURE;
  }


  // check for extra 
  if(optind != argc){
    fprintf(stderr,EXTRA_ARGS,argv[0]);
    fprintf(stderr,SHORT_CREATE_USAGE);
    return EXIT_FAILURE;
  }

  
  // build up the hashtables
  errno = 0;
  table_t  htbl; 
  table_t  rtbl;
  table_t  eotbl;

  htbl.tbl = calloc(size,sizeof(void*)); 
  rtbl.tbl = calloc(size,sizeof(void*)); 
  eotbl.tbl = calloc(size,sizeof(void*)); 

  htbl.size = size;
  rtbl.size = size;
  eotbl.size = size;

  // check if error during mem allocation
  if(htbl.tbl == NULL || rtbl.tbl == NULL || eotbl.tbl == NULL || errno != 0){
    free(htbl.tbl);
    free(rtbl.tbl);
    free(eotbl.tbl);
    // print out error msg
    perror(MEM_ERR);
    fprintf(stderr,SHORT_CREATE_USAGE);
    return EXIT_FAILURE;
  }

  // mem allocation success 
  populateTables(&htbl,&rtbl,&eotbl,fp);
  // write the content to the output file
  writeTables(output,&htbl,&rtbl,&eotbl);

  // task done, free d.a.m
  for(int k = 0; k < size; k++){
    freeLinkedList(eotbl.tbl[k]);
  }
  free(htbl.tbl);
  free(rtbl.tbl);
  free(eotbl.tbl);

  return EXIT_SUCCESS;

}
