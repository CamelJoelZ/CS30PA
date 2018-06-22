/*
 * Filename: main.c
 * Author: Zhuoer Wen
 * Userid: cs30xgz
 * Description: main driver to run the program 
 * Date: May/21/2018
 * Sources of Help: Manpage
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>


#include "pa3.h"
#include "pa3Strings.h"


/*
 * Function Name: main() 
 *
 * Function Prototype: int main( int argc, char * argv[] ); 
 *               
 * Description : This is the main driver for your program. Its main tasks  
 *               are to parse thecommand line arguments, build the hashtable
 *               of name data,and enter user interactive mode.
 *               The user will specify whether to display this information as
 *               a graph or as a list of statistics.
 *
 * Parameters: int argc, char * argv[] 
 * Side Effects: None
 * Error Condition: 1. getopt() indicates an invalid flag or missing flg
 *                  2. convertStr() detects an error
 *                  3. Extra arguments detected after getopt() completes
 *                  4. Table size is not in range
 *                  5. Ran out of memory when allocating the array
 *                  6. populateNameData() failed to populate the namesTable 
 *
 * Return Value: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 *
 */
int main( int argc, char * argv[] ){
  
  // local var
  long tableSize = 0;
  char * dirName = NULL;

  // parse tthe flags entered
  int opt;

  while ((opt = getopt(argc, argv, ARG_STR)) != -1) {
    switch (opt) {

    // help flag
    case CHAR_HELP_FLAG:
      printf(STR_USAGE_LONG,argv[0],MIN_SIZE,MAX_SIZE);
      return EXIT_SUCCESS;
      break;

    // parse hash table size
    case CHAR_SIZE_FLAG:
      if(optarg != 0){
        int errorFlag;
        tableSize = convertStr(optarg,&errorFlag);
        // error converting
        if(tableSize == -1 || errorFlag == 1){
          fprintf(stderr,STR_USAGE_SHORT,argv[0],argv[0]);
          return EXIT_FAILURE;
        }
        break; 
      }

    case CHAR_DIR_FLAG: 
      // check if there is arg
      if(optarg != 0){
        dirName = optarg;
        break;
      }
    
    // invalid option or missing arguments
    default:
      fprintf(stderr,STR_USAGE_SHORT,argv[0],argv[0]);
      return EXIT_FAILURE;
    }
  }     
    // check for extra arguments
    if(optind != argc){
      fprintf(stderr,STR_ERR_EXTRA_ARGS,argv[optind]);
      
      fprintf(stderr,STR_USAGE_SHORT,argv[0],argv[0]);
      return EXIT_FAILURE;
    }

    // set to default value if not specified
    if(tableSize == 0) tableSize = DEFAULT_SIZE;
    if(dirName == NULL) dirName = DEFAULT_DIR;

    // check for the size of table 
    if(isInRange(tableSize,MIN_SIZE,MAX_SIZE) != 1){
      fprintf(stderr,STR_ERR_RANGE,STR_ERR_SIZE,MIN_SIZE,MAX_SIZE);
      return EXIT_FAILURE;
    }
    
    // allocate memory for tableEntry
    struct tableEntry * tEntry = calloc(tableSize,sizeof(struct tableEntry));

    // memory allocation failure
    if(tEntry == NULL){
      free(tEntry); 
      fprintf(stderr,STR_ERR_MEM_EXCEEDED);
      return EXIT_FAILURE;
    }

    // initialize namesTable 
     // declare a struct here 
    struct namesTable nTable; 
    nTable.entryPtr = tEntry;
    nTable.size = tableSize;

    // populate the nameData field
    int ret = populateNameData(&nTable, dirName);
    // check if populate successfully
    if(ret != 0){
      // free tableEntry
      free(tEntry);
      return EXIT_FAILURE;
    }
     
    // if succesfully populate the field
    handleUserInput(&nTable);

    // deallocate nameData 
    for(int i = 0; i < tableSize; i++){
      free((tEntry + i) -> dataPtr);
    }
    // free tableEntry
    free(tEntry);

    // return success
    return EXIT_SUCCESS;
}
