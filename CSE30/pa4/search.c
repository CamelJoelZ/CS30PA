/*
 * Filename: search.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Descriptions: This function performs the functionality 
 *               for the search program. 
 *            
 * Date: June/02/2018
 * Sources of Help: Manpage
 */ 

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>

#include "pa4.h"
#include "pa4Strings.h"


/*
 * Function Name: search.c 
 *
 * Function Prototype: int main( int argc, char * argv[] );  
 *
 * Description: This function performs the functionality for the search
                program. It starts by parsing the command line arguments,
                handling any erros encountered in the process; then it 
                creates the hash tables and fills them by reading from 
                the input file. Finally it performs an interactive search 
                and prints stats if needed. 
 *            
 * Parameters: int argc, char * argv[]
 * Side Effects: print out usage and error message accordingly
 * Error Condition: 1.Error calling fopen
 *                  2. No input file specified
 *                  3. Extra arguments for the input flags
 * Return Value: 1 if an error occurs; 0 otherwise 
 *
 */
int main( int argc, char * argv[] ){
  int opt;
  int printable = 0;
  int hasInfile = 0;
  FILE * infile;
  while((opt = getopt(argc,argv,SEARCH_FLAGS)) != -1){
    switch(opt){

    // infile flag
    case INFILE_FLAG:
      errno = 0;
      infile = fopen(optarg,"r");
      if(errno != 0 || infile == NULL){
        perror(RTABLE_FILE_ERR);
        fprintf(stderr,SHORT_SEARCH_USAGE);
        return 1;
      }
      hasInfile = 1;
      break;
    // help flag
    case HELP_FLAG:
      printf(LONG_CREATE_USAGE);
      return 0;
  
    // stats flag
    case STATS_FLAG:
      printable = 1;
      break;
    default:
        fprintf(stderr,SHORT_SEARCH_USAGE);
        return 1;
    
    }
  }

  // If we didn't see an input file
  if(hasInfile != 1){
    fprintf(stderr,  MISSING_INFILE);
    fprintf(stderr, SHORT_SEARCH_USAGE);
    return 1;
  }

  // If we saw extra args
  if(optind != argc){
    fprintf(stderr, EXTRA_ARGS,argv[0]);
    fprintf(stderr, SHORT_SEARCH_USAGE);
    return 1;
  }

  // create 3 tables
  table_t  htbl; 
  table_t  rtbl;
  table_t  eotbl;
  
  // fill them by reading from the specified input file
  readTables(infile,&htbl,&rtbl,&eotbl);
  

  // Perform interactive search
  int counts[IN_TABLE + 1] = {0};
  beginUserQuery(counts,&htbl,&rtbl,&eotbl,printable);
  

  // task done, free d.a.m
  for(int k = 0; k < htbl.size; k++){
    freeLinkedList(eotbl.tbl[k]);
  }
  free(htbl.tbl);
  free(rtbl.tbl);
  free(eotbl.tbl);

  return 0;
}
